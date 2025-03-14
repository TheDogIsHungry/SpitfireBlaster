
// LIBRARIES  =============================================================================

#include <Servo.h> //handles pwm signal output
#include "Display.h" // Handles all screen functions and outputs.
#include <debounce.h>

// DEFINES ================================================================================

#define trigger 18
#define solenoid_mosfet 6
#define SEMI 2 
#define BURST 3
#define AUTO 4 
#define BINARY 5
#define tach_0 14
#define tach_1 15
#define escPin 11

Servo ESC1; //esc objects set up
#define MAXRPM 40000
#define MINRPM 5000

#define FORWARD 0
#define MIDDLE 1 
#define REAR 2
#define switch_pin_1 20
#define switch_pin_2 19
#define SWITCHREAD_1 digitalRead(switch_pin_1)
#define SWITCHREAD_2 digitalRead(switch_pin_2)


// LOGIC VARIABLES ==========================================================================

String motorState = "idle";  //default at rest
String pushState = "idle";
long timeInPushState = 0; //used to calculate time it took solenoid to actuate for delay
int shotDelay;  //delay needed to match desired dps
int dartQueue = 0; //dart cache
int targetRPM = 10000;
bool binaryhold = 0; //binary temp queue
const int escOff = 1000;
const int escOn = 2000;
double delaySolenoid; //calculated time based on dps. used in further calculation for realtime delay based on seensor data


// TACH VARIABLES ===========================================================================
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

volatile boolean drive0TachValid = false;  //Make sure we received fresh data before acting on it
volatile boolean drive1TachValid = false;
bool firstRun = true;
bool selftestTachState; 
int selftestTachIntegChecks;
bool tachAlert = false;
int goodTachCount = 0;
int selftestTachMulligans;
unsigned long selftestTimeStartedTaching;




uint8_t switchPos;
uint8_t switchPosPrev;

// FUNCTIONS =================================================================================

void selfTest(){
  delay(500);

  //Motor 1 wiring check
  selftestTachIntegChecks = 0;  //counter                                   
  selftestTachState = digitalRead(tach_0);//initial logic state
  while (selftestTachIntegChecks < 10) {  //Loop until enough checks done
    if (selftestTachState == digitalRead(tach_0)) { //Same logic state?
      Serial.print(selftestTachState);
      Serial.print(" ");
      selftestTachIntegChecks++;//Yes - Increment counter
      delayMicroseconds(300); //Wait 1 polling period before next read
    } else {   //Landed here: Pin changed state while we were looking at it. FAILED
      errorCode(1, 1);  //error type 1, wiring of motor 1
    }
  }
  Serial.println("motor 1 passed");
  //Motor 2 wiring check
  selftestTachIntegChecks = 0; //repeat of above
  selftestTachState = digitalRead(tach_1);                              
  while (selftestTachIntegChecks < 10) {  
    if (selftestTachState == digitalRead(tach_1)) {                     
      Serial.print(selftestTachState);
      Serial.print(" ");
      selftestTachIntegChecks++;                                   
      delayMicroseconds(300);                
    } else {                                                       
      errorCode(1, 2);  //error type 1, wiring of motor 2       
    }
  }
  Serial.println("Motor 2 passed");
  //End tach integrity checks.


  //Cleared to enable interrupts.
  attachInterrupt(digitalPinToInterrupt(tach_0), revCount0, RISING);
  attachInterrupt(digitalPinToInterrupt(tach_1), revCount1, RISING);
  drive0TachValid = false;    //reset tach validity flag                                   
  drive1TachValid = false;

  //Motor 1 spin test
  setESC(escOn); //turn on motor
  selftestTimeStartedTaching = millis(); //start timestamp
  while (!drive0TachValid) { //Loop while still invalid
    if ((millis() - selftestTimeStartedTaching) > 1000) { //if a tach is received before 1 second, pass
      errorCode(2, 1);   //else, error code from tach timeout                                                
    }
  }
  goodTachCount = 0;                       
  selftestTachMulligans = 0;                                      
  while (goodTachCount < 20) { //we want 20 good tachs
    delayMicroseconds(4800); //Abuse pulse period we're looking for as appropriate polling period to check for it
    if (pulseLength0 < 4800) { //if motor is spinning above floor speed
      goodTachCount++;  //good +1
    } else {
      selftestTachMulligans++;  //spinning under floor = bad +1                                   
    }
    if (selftestTachMulligans > 7) {   //if 7+ bad reads     
      goodTachCount = 0; //startover test and bad read count
      selftestTachMulligans = 0;
    }
    if ((millis() - selftestTimeStartedTaching) > 1000) { //regardless of how many resets, as long as we reach 20 good tachs before we reach 7 good tachs this test passes
      errorCode(3, 1);   //if the previous test and this one also does before 1 second, move on. else, error code. spin error.
    }
  }                                                                
  setESC(escOff);    //motor 1 passes both spin tests, turn off                                              
  delay(150);       //wait abit to prevent the current spinning motor from messing with the next motor tests                                               
  drive1TachValid = false;


  //Motor 2 spin test
  setESC(escOn);                                                        
  selftestTimeStartedTaching = millis();                           
  delay(10);
  while (!drive1TachValid) {                                       
    if ((millis() - selftestTimeStartedTaching) > 1000) {
      errorCode(2, 2);                                                   
    }
  }                                                                
  goodTachCount = 0;                                               
  selftestTachMulligans = 0;                                      
  while (goodTachCount < 20) {
    delayMicroseconds(4800);                      
    if (pulseLength1 < 4800) {
      goodTachCount++;                                             
    } else {
      selftestTachMulligans++;                                     
    }
    if (selftestTachMulligans > 7) {        
      goodTachCount = 0;
      selftestTachMulligans = 0;
    }
    if ((millis() - selftestTimeStartedTaching) > 1000) {
      errorCode(3, 2);                                                   
    }
  }                                                                
  setESC(escOff);  
  //both motors passed all tests, disable interrupts now
  detachInterrupt(digitalPinToInterrupt(tach_0)); 
  detachInterrupt(digitalPinToInterrupt(tach_1));                                        
  drive0TachValid = false;   //reset flags, no longer needed                                      
  drive1TachValid = false;
  goodTachCount = 0; //reset count
  //End flywheel drive checks.
}

void errorCode(int errorMajor, int errorMinor) {
  //Terminal error handler: Invoked when further operation is unsafe or impossible. Blips out error code on leds
  //Zero flywheel drive throttle to ensure anything that happened during the fault gets shut off
  setESC(escOff);
  detachInterrupt(digitalPinToInterrupt(tach_0)); //fully detach interrupts to stop data in from those pins
  detachInterrupt(digitalPinToInterrupt(tach_1));

  #ifdef switch
  #undef switch
  #endif
  switch(errorMajor){ //serial error handler
    case 1:
      Serial.println("1: wire error");
      Serial.println("Tach integrity fault");
      break;
    case 2:
      Serial.println("2: Spin error");
      Serial.println("Tachs not received");
      break;
    case 3:
      Serial.println("3: Spin error");
      Serial.println("Invalid Tachs received");
      break;
    default:
      break;
  }

  switch(errorMinor){
    case 1:
      Serial.println("Motor 1");
      break;
    case 2:
      Serial.println("Motor 2");
      break;
  }

  while (true) {
    digitalWrite(LED_BUILTIN, LOW); //3 second off period
    delay(3000);

    for (int i = 0; i < errorMajor; ++i) { //error type code
      digitalWrite(LED_BUILTIN, HIGH); //1 = wiring error       2 = tach integrity error          3 = spinning error
      delay(700);
      digitalWrite(LED_BUILTIN, LOW);
      delay(700);
    }

    for (int i = 0; i != 3; ++i) { //gap between error codes with 3 quick flashes
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
    }
    delay(500);

    for (int i = 0; i < errorMinor; ++i) { //which motor has the error
      digitalWrite(LED_BUILTIN, HIGH);
      delay(700);
      digitalWrite(LED_BUILTIN, LOW);
      delay(700);
    }
  } //Loop for eternity, there's nothing more to be done
  tachAlert = true;
}

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
      case BINARY: //binary
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

uint8_t getSwitchPosition() {
 if (!SWITCHREAD_1 && SWITCHREAD_2) {       // Forward
     return FORWARD; 
   } else if (SWITCHREAD_1 && SWITCHREAD_2) {  // Middle
     return MIDDLE; 
   } else if (SWITCHREAD_1 && !SWITCHREAD_2) { // Rear
     return REAR; 
   }
   return 0;
}

void fire(){
  if(stabalized == 0){
    attachInterrupt(digitalPinToInterrupt(tach_0), revCount0, RISING);        //pin 2 is our interrupt
    attachInterrupt(digitalPinToInterrupt(tach_1), revCount1, RISING);
  }
  setESC(escOn); 

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



//man the updatespeed function is stupid hard to understand but essential. 
//update the Flyshot set speed via PWM signal (thanks dpairsoft!)
void updateSpeed(long RPM, byte attempts) {
  speedOffsetMargin = map(RPM, MINRPM, MAXRPM, 45, 22);
  Serial.print("Starting update with requested rpm: ");
  Serial.println(RPM);
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
        digitalWrite(escPin, HIGH);
        delayMicroseconds(100);
        digitalWrite(escPin, LOW);
        delayMicroseconds(500);
      }
    }

    // Send the trailing throttle-range pulse
    digitalWrite(escPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(escPin, LOW);
    delayMicroseconds(10);
  }

 ESC1.attach(escPin, escOff, escOn);
 Serial.println("Finish speed update");
}

void setup(){
  EEPROM.begin(21);  
  Serial.begin(9600);   //debugging
  display_init();
  while(!Serial){} //wait for serial
  Serial.println("Starting setup... \n "); 
  targetRPM = 5000; //setup min rpm for testing
  updateSpeed(targetRPM, 5);
  Serial.print("esc started with testing rpm: ");
  Serial.println(targetRPM);


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

  switchPos = getSwitchPosition(); //check switch pos
  switchPosPrev = switchPos; //update
  loadvalues(switchPos);  //load values based on current switch pos
  delay(100);
  //display_init(); BETA
  Serial.println(" ");
  Serial.println("Pins set, screen initialized, values loaded");


  Serial.println("Loading menu and eeprom...");
  lastStateCLK = digitalRead(clockPin);
  Serial.print(menuState); 
  Serial.println(":  Started from setup");
  for(int i = 1; i < 22; i++) {
    Serial.print(EEPROM.read(i)); 
    Serial.print(",");
    //mainScreen(); BETA
  }

  ESC1.attach(escPin, escOff, escOn);  //defining pins for escs
  setESC(escOff); //makes sure we can send initialization
  Serial.println(" ");
  Serial.println("Setup complete");
  Serial.print("\n\n\n");
}


void loop() {
  if( firstRun == true){
    delay(800);
    Serial.println("self testing...");
    selfTest();
    Serial.println("finished self testing");
    delay(1500);

    targetRPM = motorspeedSetting; //after testing, set esc to current mode speed
    Serial.print("Now loading new rpm: ");
    Serial.println(targetRPM);
    updateSpeed(targetRPM, 10);
    Serial.print("\n\n\n");
    Serial.println("Current values that matter: ");
    Serial.print("rpm: ");
    Serial.println(targetRPM);
    Serial.print("mode #: ");
    Serial.println(modeSetting);
    setESC(escOff); //Force motors off
    firstRun = false; //set flag
    Serial.println("first run done");
    delay(1500);
    mainScreen();
  }

  /* 
  BETA removed because no battery yet
  (voltageRead() > 13.5) ? mainScreen() : lowbatteryScreen();
  */ 

 switchPos = getSwitchPosition();
 if(switchPos != switchPosPrev) {
   loadvalues(switchPos); 
   mainScreen();
 }
 switchPosPrev = switchPos;

  if (!BUTTONHIGH) {                   // If encoder button is pressed, ground signal sent.
    settingsMenu();                    // Break to settings menu.  
    if(menuState == "Save") { savevalues(counter); }
    menuState = "Main Menu";           // When done with settings menu, update menuState to reflect going back to Main Menu.
    switchPos = getSwitchPosition();
    loadvalues(switchPos);
    mainScreen(); 
    return; 
  }


  if(stabalized == 0){
    digitalWrite(LED_BUILTIN, LOW);
  }

  if(targetRPM != motorspeedSetting) {      // TODO 3 position switch state check
    targetRPM = motorspeedSetting; 
    updateSpeed(targetRPM, 5); 
    Serial.println("UPDATED");
    setESC(escOff);
    delay(1000);
  }

  // Main operation ------------------------------------------------------------------------                             // Load current values from persistent memory.
  triggerButton.update(digitalRead(trigger));  // Check for trigger state change.

 
  Serial.print("Dart Queue");
  Serial.println(dartQueue);
  //Serial.print("stab: ");
  //Serial.println(stabalized);
  //Serial.println(motorState);
  //Serial.println(newTimeStamp);


 
  if(dartQueue > 0){  //darts in queue, move to main firing actions
    delaySolenoid = delayCalc(dpsSetting);  //calculate delay with previously loaded values
    fire(); //move to main logic
    
  }else if(binaryhold == 0 && motorState != "hang"){
    stabalized = 0;
  }

  // RPM ----------------------------------------------------------------------------------
  if (newTimeStamp) { 
    noInterrupts(); // Disable interrupts temporarily
    newTimeStamp = false; // Clear the flag
    count++; // Increment count to limit printing frequency

    // Calculate RPM
    unsigned long timeDiff0 = pulseLength0;
    unsigned long timeDiff1 = pulseLength1;
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


void revCount0() { //called everytime the isr receives a pulse
  newTimeStamp = true; // flag to tell main code to read the value of timeStamp
  lastPulseTime0 = thisPulseTime0;
  thisPulseTime0 = micros();
  pulseLength0 = thisPulseTime0 - lastPulseTime0;
  drive0TachValid = true;
}

void revCount1() { //called everytime the isr receives a pulse  
  newTimeStamp = true; // flag to tell main code to read the value of timeStamp
  lastPulseTime1 = thisPulseTime1;
  thisPulseTime1 = micros();
  pulseLength1 = thisPulseTime1 - lastPulseTime1;
  drive1TachValid = true;
}
