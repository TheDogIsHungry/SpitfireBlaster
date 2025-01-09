
// LIBRARIES ===========================================================================================

#include <Adafruit_SSD1306.h> //screen 
#include "Bitmaps.h" 
#include "MemoryManager.h"    // EEPROM functions.

// DEFINES ================================================================================================

#define SET 0 
#define clockPin 7
#define dtPin 8
#define buttonPin 9

#define FRAME_DELAY (2)
#define FRAME_WIDTH (48)
#define FRAME_HEIGHT (48)
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))

#define BUTTONHIGH digitalRead(buttonPin)
#define CLOCKCHECK digitalRead(clockPin)
#define DTCHECK    digitalRead(dtPin)

// SCREEN PARAMETERS ===================================================================================-

Adafruit_SSD1306 Display(128, 64); //define for the screen

typedef struct {
String hoverLabel; 
int x; 
int y; 

} hover;

hover hoverOver[13] {
  
{"Back", 1, 54}, 
{"DPS:", 1, 15}, 
{"Motor:", 1, 23},
{"Brake:", 1, 31},
{"Hang:", 1, 39},
{"Comp:", 69, 15},
{"Mode:", 69, 23},
{"BSize:", 69, 31},
{"Save", 105, 54},
{"Forward", 25, 15},
{"Middle", 25, 23},
{"Rear", 25, 31},
{"Back", 52, 54},

};

String wordGuys[9] = {"Low", "Med", "High", "Off", "On", "Semi", "Bst", "Auto", "Bin"};  // Non numerical display for tournament mode and fire mode.

int frame = 0;			      // Animation stuff.
uint16_t counter = 1;                 // Incremented / decremented to define where user is hovering (what to highlight), as well as what value to select.
uint8_t counterGhost = 1;             // When entering paramter menu, "Motor" for example, which indexed at 2, remember this position to return to it in master settings screen.
uint8_t lowerBound;               // Defines lower bound for menus, 0 - 7 in master settings menu encompasses 'Back' to 'Save', 0 - 4000 for hang setting, etc. 
uint16_t upperBound;              // Defines upperbound of what was explained above. 
uint8_t currentStateCLK;          
uint8_t lastStateCLK;             
unsigned long lastButtonPress = 0;  // Takes timestamp of button press using millis()

// FUNCTIONS ============================================================================================

int counterLength(int i) {    // Function to do some math to center labels and numbers properly depending on length, 1 = 1, "Hi" = 2, 500 = 3 etc. 
 if (i == 0) {return 1;} 
    return log10(i) + 1;
}

void waitHigh() {             // After button press, wait for it to be depressed to avoid chaining if statements. 
  while(1) {
    if(BUTTONHIGH) {
      return;  
    }
  } 
}

float voltageRead() {
  return ((analogRead(26)) * (5.0 / 1023.0)) * ((10000.0 + 4200.0) / 4200.0); 
}

void display_init() {         // Initializes screen, displays splash.
  Display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  Display.clearDisplay();
  Display.display();
  Display.setCursor(0, 0);
  Display.setTextColor(1); //white text for boot screen;
  Display.setTextSize(1);
  Display.setTextWrap(false);
  Display.clearDisplay();
  Display.drawBitmap(0, 0, splash, 128, 64, 1);

  
  Display.setCursor(60,0);
  Display.println("Warthog");
  Display.setCursor(92,54);  
  Display.println("0.12.1");
  Display.setCursor(100, 34);
  Display.println("Baja");
  Display.setCursor(90, 44);
  Display.println("Blstrs");
  
  Display.display();

}

// MAIN MENU ----------------------------------------------------------

void mainScreen() {

  Display.clearDisplay();
  Display.setTextSize(1);
  Display.setTextColor(WHITE); 

  Display.setCursor(30, 0);
  Display.print("Spitfire");
  Display.drawLine(30, 8, 76, 8, 1);
  Display.setCursor(0, 55);
  Display.print("Beta0.12.1");
  Display.setCursor(89, 0); 
  Display.print(voltageRead()); 
  Display.print("V"); 
  Display.setCursor(111 - ((profileSwitch.length() - 3) * 6), 55);  // Keep "Forward", "Middle", "Rear", as far right as possible. 
  Display.print(profileSwitch); 
  Display.setCursor(0, 15);
  Display.print("DPS:  ");
  Display.println(dpsSetting);
  Display.print("Motor:");
  Display.print((motorspeedSetting - 1000) / 10);
  Display.println("%");
  Display.print("Brake:");
  Display.println(wordGuys[brakeamountSetting]);       // Setting in memory mapped to String in wordGuys array.
  Display.print("Hang: ");
  Display.print(hangtimeSetting);
  Display.println("ms");
  Display.setCursor(69, 15); 
  Display.print("Comp: ");
  Display.print(wordGuys[compSetting]);   
  Display.setCursor(69, 23);
  Display.print("Mode: ");
  Display.println(wordGuys[modeSetting]);
  if(modeSetting == 6) {			// If fire mode is 6 (Burst), display BSize.
  Display.setCursor(69, 31); 
  Display.print("BSize:");
  Display.print(burstSetting);
  }
  
  Display.display();
}


void settingScreen(int counterCopy) {   // Contains settings master menu, parameter menu, save menu.


// SETTINGS MASTER MENU --------------------------------------------------------------------------------
Display.clearDisplay(); 
  if(menuState == "Settings") {

  Display.setTextSize(1);		//  Static labels.
  Display.setTextColor(1);	        // White. 
  Display.setCursor(40, 0);          
  Display.print("Settings");
  Display.drawLine(40, 8, 86, 8, 1);
  Display.setCursor(0, 15);
  Display.print("DPS:  ");
  Display.println(dpsSetting);
  Display.print("Motor:");
  Display.print(motorspeedSetting);
  Display.println("%");
  Display.print("Brake:");
  
  Display.println(wordGuys[brakeamountSetting]);
  Display.print("Hang: ");
  Display.print(hangtimeSetting);
  Display.println("ms");
  Display.setCursor(69, 15); 
  Display.print("Comp: ");
  Display.print(wordGuys[compSetting]);
  Display.setCursor(69, 23); 
  Display.print("Mode: ");
  Display.print(wordGuys[modeSetting]);
  if(modeSetting == 6) {				// If fire mode is 6 (Burst), display BSize to allow user to change.
  Display.setCursor(69, 31); 
  Display.print("BSize:");
  Display.print(burstSetting);
  }
  Display.setCursor(105, 54); 
  Display.println("Save");
  Display.setCursor(1, 54);
  Display.print("Back");
	  
  Display.setTextColor(0); 	// Black.
	  
  //fillRect params, x, y, w, h	  			
  Display.fillRect(hoverOver[counterCopy].x - 1, hoverOver[counterCopy].y - 1, (hoverOver[counterCopy].hoverLabel.length() * 6), 10, 1);	// Dynamic labels, displays highlight over hovered parameter.	
  Display.setCursor(hoverOver[counterCopy].x, hoverOver[counterCopy].y); 
  Display.print(hoverOver[counterCopy].hoverLabel); 

  Display.display();
  return; 
}

// PARAMETER MENUS ------------------------------------------------------------------------------------

if(menuState != "Settings" && menuState != "Save") {     // When entering parameter menus, display accordingly. 
  Display.setTextSize(2);
  Display.setTextColor(1); //white
  Display.setCursor(52 - ((menuState.length() - 3) * 6), 0);    // Aforementioned math to center numbers and labels, one digit or character is ~ 6 pixels. Start at 3 for label "DPS:" as reference
  Display.print(menuState);
  Display.setCursor(64 - (counterLength(counterCopy) * 6), 24); // Start at 1 for single digit. Each subsequent digit or character subtracts another 6, to keep centered.
  if(menuState == "Comp:" || menuState == "Mode:" || menuState == "Brake:") {
    Display.setCursor(64 - (wordGuys[counterCopy].length() * 6), 24);
    Display.print(wordGuys[counterCopy]);                     // Display strings in wordGuys instead of counter # depending on menuState.
  }
  else {
  Display.print(counterCopy);                                // All other parameters are numerical.
  }
  Display.display();
  return; 
 }

// SAVE MENU ------------------------------------------------------------------------------------

if(menuState == "Save") {     // Save menu. Allows to save to specific switch position.
  Display.setTextSize(1);
  Display.setTextColor(1); 
  Display.setCursor(40, 0);
  Display.print("Save to:");
  Display.drawLine(40, 8, 81, 8, 1);
  Display.setCursor(25, 15);
  Display.print(hoverOver[9].hoverLabel);
  Display.setCursor(25, 23);
  Display.print(hoverOver[10].hoverLabel);
  Display.setCursor(25, 31);
  Display.print(hoverOver[11].hoverLabel);
  Display.setCursor(52, 54);
  Display.print(hoverOver[12].hoverLabel);

  Display.fillRect(81, 15, 9, 8, 1);
  Display.drawRect(89, 15, 9, 8, 1);
  Display.drawRect(97, 15, 9, 8, 1);
  
  Display.drawRect(81, 23, 9, 8, 1);
  Display.fillRect(89, 23, 9, 8, 1);
  Display.drawRect(97, 23, 9, 8, 1);

  Display.drawRect(81, 31, 9, 8, 1);
  Display.drawRect(89, 31, 9, 8, 1);
  Display.fillRect(97, 31, 9, 8, 1);

  Display.setTextColor(0); 

  Display.fillRect(hoverOver[counterCopy].x - 1, hoverOver[counterCopy].y - 1, (hoverOver[counterCopy].hoverLabel.length() * 6), 10, 1);
  Display.setCursor(hoverOver[counterCopy].x, hoverOver[counterCopy].y); 
  Display.print(hoverOver[counterCopy].hoverLabel); 

  Display.display();
  return; 
  }
  // END OF settingScreen.
 }



void rebootingScreen(){         // Called when rebooting.
  Display.clearDisplay();
  Display.setTextSize(2);
  Display.setTextColor(1); 
  Display.setCursor(10, 20);
  Display.print("Saving...");
  Display.display();
}

void lowbatteryScreen() {     // Called when battery voltage is under limit.
    Display.setTextSize(1);
    Display.setTextColor(1);
    Display.clearDisplay();
    Display.drawBitmap(40, 0, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
    Display.setCursor(31, 50);
    Display.print("Low Battery");
    Display.display();
    frame = (frame + 1) % FRAME_COUNT;
    delay(FRAME_DELAY);
}


void setCounter(int counterCopy, uint8_t counterGhostCopy) {                //Setting upper and lower bound of counter depending on menu, set menuState.

menuState = hoverOver[counterCopy].hoverLabel;                              // Cheap way to keep menuState, correspond counter to index in hoverLabel, EX hoverOver[1].hoverLabel = "DPS:". 
  switch(counterCopy) {
    case SET:                            // Settings Menu. Macro SET = 20
     lowerBound = 0; 
     upperBound = 8;
     menuState = "Settings";           // manually set to "Settings".
     counter = counterGhostCopy;       // Reset at previously selected parameter.
      break;
    case 1:   // DPS.
     lowerBound = 1;                  // Set upper and lower bound for given parameter menu, DPS can be selected from 1 - 10, for example.
     upperBound = 10;
     counter = dpsSetting;            // Once a parameter menu is displayed, set counter to value to current (parametername)Setting
     break; 
   case 2:   // MotorSpeed.
     lowerBound = 1; 
     upperBound = 100;
     counter = motorspeedSetting; 
     break;
   case 3:  // Brake. 
     lowerBound = 0; 		    // Brake, Tournament Mode (Comp), and Fire mode (Mode) display strings instead of numerical values. Upper and lower limits mapped to wordGuys array.
     upperBound = 2;
     counter = brakeamountSetting; 
     break;
  case 4:   // Hangtime.
     lowerBound = 0; 
     upperBound = 4000; 
     counter = hangtimeSetting; 
     break;
  case 5:   // Tournament Mode.
     lowerBound = 3; 
     upperBound = 4;
     counter = compSetting; 
     break; 
  case 6:   // Fire Mode.
     lowerBound = 5; 
     upperBound = 8; 
     counter = modeSetting; 
     break; 
  case 7:  // Burst amount.
     lowerBound = 2; 
     upperBound = 5;
     counter = burstSetting; 
     break;
  case 8:  // Save menu.
     lowerBound = 9; 
     upperBound = 12;
     counter = 9; 
     break;
  }
    return; 
}

void saveenteredValue(uint8_t counterGhostCopy, int counterCopy) {      // Save parameter value according to current screen, not saved in EEPROM until savevalues() is called. 

  switch(counterGhostCopy) {
    case 1: 
    dpsSetting = counterCopy; 
    break;
    case 2: 
    motorspeedSetting = counterCopy;
    break;
    case 3: 
    brakeamountSetting = counterCopy;
    break;
    case 4: 
    hangtimeSetting = counterCopy; 
    break;
    case 5: 
    compSetting = counterCopy;
    break;
    case 6: 
    modeSetting = counterCopy; 
    break;
    case 7: 
    burstSetting = counterCopy;
    break;
  } 
return; 
}


void settingsMenu() {          // Master function, calls previous functions to update screen according to counter and menuState values, detects button press and encoder scrolls.

  waitHigh(); 		     				// On function call, wait for high signal.
  motorspeedSetting = (motorspeedSetting - 1000) / 10;  // Converting runtime value into percentage. 
  setCounter(SET, counterGhost);                        // Set master settings menu upper and lower bound.
  settingScreen(counter);				// Display master settings menu first.


  while(menuState != "Main Menu") {                     // Runs until broken from via back button or save button. 

    if(voltageRead() < 13.5) {				// Check battery in settings menu.
       while(1) {
        lowbatteryScreen(); 
       }
     }           
	  
   currentStateCLK = CLOCKCHECK; 

    if(currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
		  // If the DT state is different than the CLK state then the encoder is rotating CCW so decrement.
		  if (DTCHECK != currentStateCLK) {
        if(counter < upperBound) {
			  (menuState == "Hang:") ? counter += 100 : counter++;     // If on hang, increment/decrement by 100, otherwise, increment by 1. 
        (menuState == "Settings" && modeSetting != 6 && counter == 7) ? counter = 8 : counter += 0; // If fire mode is not 6 (Burst), skip over the array element that contains BSize.
        }
		  } else {
        if(counter > lowerBound) {
			  (menuState == "Hang:") ? counter -= 100 : counter--; 
        (menuState == "Settings" && modeSetting != 6 && counter == 7) ? counter = 6 : counter -= 0; 
       }
		  }  
      settingScreen(counter);
	}

  lastStateCLK = currentStateCLK;     


	if (!BUTTONHIGH) {	// Encoder button pressed.

    if (millis() - lastButtonPress > 50 && (menuState == "Settings" && counter == 0) || (menuState == "Save" && counter != 12)) { // If back button pressed on settings, or save position selected in save menu, break, return to void loop()
      waitHigh();
      counter = 1; 														 // Reset counter and counterGhost for future.
      counterGhost = counter;  
      break; 
    }
    if (millis() - lastButtonPress > 50 && menuState != "Settings") {      // If in any other menu than master settings page, return to it.
      waitHigh();
      saveenteredValue(counterGhost, counter);                                          // Save value entered according to counterGhost and current value of counter.
      setCounter(SET, counterGhost);                                                    // Return to master settings menu settings. lmao
      settingScreen(counter);                                            
      continue;                                                                         // Return to beginning of for loop to avoid chain if statement
		}
    if (millis() - lastButtonPress > 50 && menuState == "Settings") {                   
      waitHigh();
      counterGhost = counter;                                                           // Remember which parameter was selected
      setCounter(counter, counterGhost);                                                // Send counter position to determine which parameter menu to display, EX: If counter value = 2, Motor parameter menu will display.
      settingScreen(counter);                                                           // Display proper parameter menu.
		}
		// Remember last button press event
		lastButtonPress = millis();
	}
	// Put in a slight delay to help debounce the reading
	delay(1);
 }
 
  return; 
}
