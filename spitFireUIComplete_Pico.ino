
// LIBRARIES  =========================================

#include <Servo.h> //handles pwm signal output
#include "Display.h" // Handles all screen functions and outputs.
#include <debounce.h>

// DEFINES =========================================

#define trigger 3
#define solenoid_mosfet 11
#define SEMI 5 
#define BURST 6
#define AUTO 7 
#define BINARY 8
Servo ESC1; //esc objects set up
Servo ESC2;


// LOGIC VARIABLES =========================================

String revState = "idle";  //default at rest
String pushState = "idle";
long timeInPushState = 0; //used to calculate time it took solenoid to actuate for delay
int shotDelay;  //delay needed to match desired dps
int owedDarts = 0; //dart cache
int firedDarts = 0;  //used for state change of a few things
int queue2; //binary temp queue
const int motorMax = 2000;  //absolute max motor will ever go
const int escLow = 1000;
const int escHigh = 2000;
int wheelSpeed = 1000;  //tracks wheel speed. Default = 1000 = 0% speed = idle. 
double delaySolenoid; //calculated time based on dps. used in further calculation for realtime delay based on seensor data


// FUNCTIONS =========================================


void manageTrigger(uint8_t btnId, uint8_t btnState){//BETA should get called automatically when debounce detects trigger updates May need to add to main
  static bool wasTriggered = false;
    if(millis() < 4000){  //startupdelay + every small additional delay
    owedDarts = 0;
    return;
  }
  if(btnState == BTN_PRESSED && !wasTriggered){ //first button press
    wasTriggered = true; //mark that it was pressed
    switch (modeSetting){
      case SEMI:  //semi, +1
        owedDarts++;
        break;
      case BURST:  //burst +2,3,4,5 depending on burstSetting picked
        owedDarts += burstSetting;
        break;
      case AUTO:  //auto, adds a amount higher than any mag to allow for a full dump but will auto stop if something goes wrong
        owedDarts += 60;
        break;
      case BINARY: //binary, IDK YET
        owedDarts ++; //add 1 dart to start
        queue2 ++; 
        break;
    }
  }else if(btnState == BTN_PRESSED &&  wasTriggered){ //now in this state
    wasTriggered = false;
    if(modeSetting == BINARY){ //if binary
      owedDarts++; //add 2nd dart
      queue2--;  //stop the queue2 thats keeping the system revved
    }else if(modeSetting == AUTO){ //if auto, and the trigger was released, remove all darts from queue
      owedDarts = 0;
    }
  }
}

static Button triggerButton(0, manageTrigger); //ID = 0 and this button only corresponds to the manageTrigger function

void setup(){
  EEPROM.begin(21);  
  Serial.begin(9600);   //debugging
  delay(100); 

  ESC1.attach(6, escLow, escHigh);  //defining pins for escs
  delay(100);
  ESC2.attach(10, escLow, escHigh);
  setESC(escLow); //makes sure we can send initialization
  delay(100);


  pinMode(trigger, INPUT_PULLUP); //how each pin should be treated 
  pinMode(switch_pin_1, INPUT_PULLUP);
  pinMode(switch_pin_2, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP); 
  pinMode(solenoid_mosfet, OUTPUT);
  pinMode(clockPin, INPUT); //rotoray encoder setup
  pinMode(dtPin, INPUT);
  triggerButton.setPushDebounceInterval(20);  //Intervals which are used to measure physical debouncing of trigger contacts
  triggerButton.setReleaseDebounceInterval(20);
  delay(100);
  display_init(); 
  delay(300);


  Serial.println("Starting up...");
  // Read the initial state of CLK
  lastStateCLK = digitalRead(clockPin);
  Serial.print(menuState); 
  Serial.print(":  Start from setup");
  owedDarts = 0;
  delay(3000); //startup delay (3 Seconds)
  for(int i = 1; i < 22; i++) {
  Serial.println(EEPROM.read(i)); 
  }
}


void pollButtons(){ //assigns trigger pin yo trigger button and updates when there is a state change on that in.
  triggerButton.update(digitalRead(trigger));
}

double delayCalc(int _dps){  //calculates delay for solenoid with error checking
  int delay = (1000 / _dps);
  if(delay < 0){
    return 0;
  }
  return delay;
}

void setESC(int speed){  //error checking for the speed sent to motor
  if(speed < escLow){
    speed = escLow;
  }
  if(speed > motorMax){
    speed = motorMax;
  }
  ESC1.write(speed);
  ESC2.write(speed);
}



void loop(){
  Serial.print(owedDarts);  //debugging

  if(voltageRead() < 13.5) { //low battery
    while(1) {
        lowbatteryScreen(); 
    }
  }

  // Main operation ---------------------------
  loadvalues(); //get values to operate
  delaySolenoid = delayCalc(dpsSetting);
  pollButtons();  //checks when trigger updates





  // Screen ---------------------------
  mainScreen();
  if (!BUTTONHIGH) {                   // Checks pin 'D9' / buttonPin on board, actually portb.1, prefer to do direct port checks than digitalRead() to speed up runtime code.
    settingsMenu();                 // Break to settings menu.  
    if(menuState == "Save") {       // If broken from save menu, call savevalues() with corresponding counter position
      savevalues(counter);          
    }   
    return;
  }
}

