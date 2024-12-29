
// LIBRARIES  =========================================

#include <Servo.h> //handles pwm signal output
#include <avr/wdt.h>  // Watchdog Reset
#include "Display.h" // Handles all screen functions and outputs.

// PINS =========================================

#define trigger 3
#define solenoid_mosfet 11
Servo ESC1; //esc objects set up
Servo ESC2;


// LOGIC VARIABLES =========================================

String revState = "idle";  //default at rest
String pushState = "idle";
long timeInPushState = 0; //used to calculate time it took solenoid to actuate for delay
int shotDelay;  //delay needed to match desired dps
int owedDarts = 0; //dart cache
const int motorMax = 2000;  //absolute max motor will ever go
const int escLow = 1000;
const int escHigh = 2000;
int wheelSlowing = 1000;


// FUNCTIONS =========================================

void setup(){
  wdt_disable();
  Serial.begin(9600);   //debugging
  delay(100); 
  ESC1.attach(6, escLow, escHigh);  //defining pins for escs
  delay(100);
  ESC2.attach(10, escLow, escHigh);
  setESC(escLow); //makes sure we can send initialization
  delay(100);
  pinMode(trigger, INPUT_PULLUP); //how each pin should be treated 
  pinMode(switch_pos_1, INPUT_PULLUP);
  pinMode(switch_pos_2, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(solenoid_mosfet, OUTPUT);
  pinMode(clockPin, INPUT); //rotoray encoder setup
  pinMode(dtPin, INPUT);
  delay(100);
  display_init(); 
  delay(300);
  Serial.println("Starting up...");
  // Read the initial state of CLK
  lastStateCLK = digitalRead(clockPin);
  Serial.print(menuState); 
  Serial.print(":  Start from setup");
  owedDarts = 0;
  delay(500); //startup delay
  for(int i = 30; i < 42; i++) {
  Serial.println(EEPROM.read(i)); 
  }
  wdt_enable(0x09<<0); // set watchdog to 2000 cycles.
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
  wdt_reset();
  loadvalues(); 
  mainScreen();
  if ((PINB & (1 << 1)) == 0) {     // Checks pin 'D9' / buttonPin on board, actually portb.1, prefer to do direct port checks than digitalRead() to speed up runtime code.
    settingsMenu();                 // Break to settings menu.  
    if(menuState == "Save") {       // If broken from save menu, savevalues(); 
      savevalues(counter);          // Send position.  
    }   else {
      loadvalues();                 // If broken from back button, load values from memory. 
    }
  }
}

