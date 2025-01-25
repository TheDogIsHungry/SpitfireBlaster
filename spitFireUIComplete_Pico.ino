
// LIBRARIES  =============================================================================

#include <Servo.h> //handles pwm signal output
#include "Display.h" // Handles all screen functions and outputs.
#include <debounce.h>

// DEFINES ================================================================================

#define trigger 18
#define solenoid_mosfet 6
#define SEMI 6 
#define BURST 7
#define AUTO 8 
#define BINARY 9
#define tach_0 14
#define tach_1 15
#define escPin 11

Servo ESC1; //esc objects set up
#define MAXRPM 40000
#define MINRPM 5000
#define targetRPM 33000



// LOGIC VARIABLES ==========================================================================

String motorState = "idle";  //default at rest
String pushState = "idle";
long timeInPushState = 0; //used to calculate time it took solenoid to actuate for delay
int shotDelay;  //delay needed to match desired dps
int dartQueue = 0; //dart cache
//int firedDarts = 0;  //used for state change of a few things  BETA may not need
bool binaryhold = 0; //binary temp queue
const int escOff = 1000;
const int escOn = 2000;
double delaySolenoid; //calculated time based on dps. used in further calculation for realtime delay based on seensor data

unsigned int speedSetpoint;
byte speedOffsetMargin;
float rpm0 = 0;
float previousRPM0 = 0;
float rpm1 = 0;
float previousRPM1 = 0;
unsigned int count = 0; //cycle count
bool newTimeStamp = false; //if there's a new timestamp
bool stabalized = 0;
volatile unsigned long thisPulseTime0;
volatile unsigned long pulseLength0;
volatile unsigned long lastPulseTime0;

volatile unsigned long thisPulseTime1;
volatile unsigned long pulseLength1;
volatile unsigned long lastPulseTime1;
// FUNCTIONS =================================================================================



static void manageTrigger(uint8_t btnId, uint8_t btnState){
  static bool wasTriggered = 0; //trig pressed flag
  if(millis() < 4000){  //startupdelay + every small additional delay
    dartQueue = 0;
    return;
  }

  if(btnState == BTN_PRESSED && wasTriggered){ //next here, released
    wasTriggered = 0; //reset trigger pressed flag
    if(modeSetting == BINARY){ //if binary
      dartQueue++; //add 2nd dart
      binaryhold = 0;  //stop the binaryhold thats keeping the system revved
    }else if(modeSetting == AUTO){ //if auto, and the trigger was released, remove all darts from queue
      dartQueue = 0;
    }
  } else if(btnState != BTN_PRESSED && !wasTriggered){ //start here. pressed
    switch (modeSetting){
      case SEMI:  //semi, +1
        dartQueue++;
        break;
      case BURST:  //burst +2,3,4,5 depending on burstSetting picked
        dartQueue += burstSetting;
        break;
      case AUTO:  //auto, adds a amount higher than any mag to allow for a full dump but will auto stop if something goes wrong
        dartQueue = 60;
        break;
      case BINARY: //binary, IDK YET
        dartQueue ++; //add 1 dart to start
        binaryhold = 1; 
        break;
    }
    wasTriggered = 1; //mark that it was pressed
  } 
}
static Button triggerButton(0, manageTrigger); //ID = 0 and this button only corresponds to the manageTrigger function


double delayCalc(int _dps){  //calculates delay for solenoid with error checking
  int delay = (1000 / _dps);
  if(delay < 0){
    return 0;
  }
  return delay;
}

void setESC(int speed){  //error checking for the speed sent to motor
  if(speed < escOff){
    speed = escOff;
  }
  if(speed > escOn){
    speed = escOn;
  }
  ESC1.writeMicroseconds(speed);
}


void fire(){
  if(stabalized == 0){
    attachInterrupt(digitalPinToInterrupt(tach_0), revCount0, RISING);        //pin 2 is our interrupt
    attachInterrupt(digitalPinToInterrupt(tach_1), revCount1, RISING);
  }
  setESC(escOn); //BETA idk where this should go, but it makes sense here

  if(motorState == "idle"){  //stared from stop
    motorState = "spooling";
  }
  if(motorState == "Braking"){  //resumed from braking
    motorState = "spooling";
  }
  if(motorState == "hang"){
    motorState = "powered";
    pushState = "idle";
    //BETA refernce STEALER but i kinda gotta wait until we get sensors set and redo logic
  }
  if(motorState == "spooling"){ //if the motors have been speeding 
    if(stabalized == 1){ //and if the motors have stabalized (reached reuqested rpm)
      pushState = "idle";
      motorState = "powered";
    }
  }


  //solenoid control
  if(motorState == "powered"){ //motors are on

    if(pushState == "idle"){ //and solenoid ready
      digitalWrite(solenoid_mosfet, HIGH); //start solenoid
      pushState = "thrusting";  //its moving now
    }
  }
}



//update the Flyshot set speed via PWM signal (thanks dpairsoft!)
void updateSpeed(long RPM, byte attempts) {
  speedOffsetMargin = map(RPM, MINRPM, MAXRPM, 45, 22);
  ESC1.detach();
  unsigned int setPoint = 320000000 / (RPM * (14 / 2));
  speedSetpoint = ((3 * setPoint) / 16);
  unsigned int packet = setPoint | 0x8000;

  for (byte pksend = 0; pksend < attempts; pksend++) {
    // Send the leading throttle-range pulse
    digitalWrite(escPin, HIGH);
    delayMicroseconds(1000);

    digitalWrite(escPin, LOW);
    delayMicroseconds(10);

    // Send the packet MSB first
    for (short j = 15; j >= 0; j--) {
      if (packet & (0x0001 << j)) {
        // Send a T1H pulse
        digitalWrite(escPin, HIGH);
        delayMicroseconds(400);
        digitalWrite(escPin, LOW);
        delayMicroseconds(500);
      } else {
        // Send a T0H pulse
        digitalWrite(escPin, escOn);
        delayMicroseconds(100);
        digitalWrite(escPin, escOff);
        delayMicroseconds(500);
      }
    }

    // Send the trailing throttle-range pulse
    digitalWrite(escPin, escOn);
    delayMicroseconds(1000);
    digitalWrite(escPin, escOff);
    delayMicroseconds(10);
  }

 ESC1.attach(escPin, escOff, escOn);
}

void setup(){
  EEPROM.begin(21);  
  Serial.begin(9600);   //debugging
  delay(100); 

  ESC1.attach(escPin, escOff, escOn);  //defining pins for escs
  setESC(escOff); //makes sure we can send initialization
  for (byte i = 0; i < 2; i++) {
    updateSpeed(targetRPM, 10);
    delay(200);
  }
  delay(100);

  //how each pin should be treated
  pinMode(trigger, INPUT_PULLUP);  
  pinMode(switch_pin_1, INPUT_PULLUP);
  pinMode(switch_pin_2, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(solenoid_mosfet, OUTPUT);
  pinMode(clockPin, INPUT); //rotoray encoder setup
  pinMode(dtPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);  //for debugging
  pinMode(tach_0, INPUT_PULLUP);
  pinMode(tach_1, INPUT_PULLUP);
  triggerButton.setPushDebounceInterval(5);  //Intervals which are used to measure physical debouncing of trigger contacts
  triggerButton.setReleaseDebounceInterval(5);
  delay(100);
  display_init(); 
  delay(1000);


  Serial.println("Starting up...");
  lastStateCLK = digitalRead(clockPin);
  Serial.print(menuState); 
  Serial.print(":  Start from setup");
  //delay(3000); //startup delay (3 Seconds)
  for(int i = 1; i < 22; i++) {
  Serial.println(EEPROM.read(i)); 
  }
}


void loop(){
  /* 
  BETA removed because no battery yet
  (voltageRead() < 13.5) ? lowbatteryScreen() : mainScreen();
  */ 
  if(stabalized == 0){
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Main operation ------------------------------------------------------------------------
  loadvalues();                                // Load current values from persistent memory.
  triggerButton.update(digitalRead(trigger));  // Check for trigger state change.
  Serial.println(dartQueue);
  Serial.print("stab: ");
  Serial.println(stabalized);
  Serial.println(motorState);
  Serial.println(newTimeStamp);

  if(dartQueue > 0){  //darts in queue, move to main firing actions
    delaySolenoid = delayCalc(dpsSetting);  //calculate delay with previously loaded values
    fire();
    
  }else if(binaryhold == 0 && motorState != "hang"){
    stabalized = 0;
  }
  // Screen -------------------------------------------------------------------------------
   mainScreen();
  if (!BUTTONHIGH) {                   // If encoder button is pressed, ground signal sent.
    settingsMenu();                    // Break to settings menu.  
    (menuState == "Save") ? savevalues(counter) : loadvalues(); 
    menuState = "Main Menu";           // When done with settings menu, update menuState to reflect going back to Main Menu.
   // return; 
  }
  // RPM ----------------------------------------------------------------------------------
  if (newTimeStamp) { 
    noInterrupts(); // Disable interrupts temporarily
    newTimeStamp = false; // Clear the flag
    count++; // Increment count to limit printing frequency

    // Calculate RPM
    unsigned long timeDiff0 = thisPulseTime0 - lastPulseTime0;
    unsigned long timeDiff1 = thisPulseTime1 - lastPulseTime1;
    if(timeDiff0 > 0){
      rpm0 = (2.0) / ((float)timeDiff0 / 60000000.0 * 14.0); // 14 poles
    } else{
      rpm0 = 0; // Prevent division by zero
    }
    if(timeDiff1 > 0){
      rpm1 = (2.0) / ((float)timeDiff1 / 60000000.0 * 14.0); // 14 poles
    } else{
      rpm1 = 0; 
    }

    // Check and print
    if (count > 0) {
      count = 0;
      Serial.println(rpm0);
      Serial.println(rpm1);
      
      if(previousRPM0 <= (rpm0 + 250.0) && previousRPM0 >= (rpm0 - 250.0) && rpm0 >= (targetRPM - 1000.0) && rpm0 <= (targetRPM + 1000.0)) {
        if(previousRPM1 <= (rpm1 + 250.0) && previousRPM1 >= (rpm1 - 250.0) && rpm1 >= (targetRPM - 1000.0) && rpm1 <= (targetRPM + 1000.0)){
          //Serial.println("Stabilizedzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
          digitalWrite(LED_BUILTIN, HIGH);
          stabalized = 1;  //BETA we need to disable stabalization when the queue is cleared
          detachInterrupt(digitalPinToInterrupt(tach_0));
          detachInterrupt(digitalPinToInterrupt(tach_1));
        }
      }
      previousRPM0 = rpm0;
      previousRPM1 = rpm1;
    }
    interrupts(); // Re-enable interrupts
  }

}


void revCount0() { //called everytime the isr receives a pulse  BETA, i need to make a 2nd tach function dude
  newTimeStamp = true; // flag to tell main code to read the value of timeStamp
  lastPulseTime0 = thisPulseTime0;
  thisPulseTime0 = micros();
}

void revCount1() { //called everytime the isr receives a pulse  BETA, i need to make a 2nd tach function dude
  newTimeStamp = true; // flag to tell main code to read the value of timeStamp
  lastPulseTime1 = thisPulseTime1;
  thisPulseTime1 = micros();
}
