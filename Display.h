
// LIBRARIES ===========================================================================================

#include "Adafruit_SSD1306.h" //screen 
#include "Splash.h" 
#include "MemoryManager.h"    // EEPROM functions.
// PINS ================================================================================================

#define SET 0 // not a pin
#define clockPin 7
#define dtPin 8
#define buttonPin 9

#define BUTTONHIGH digitalRead(buttonPin)
#define CLOCKCHECK digitalRead(clockPin)
#define DTCHECK    digitalRead(dtPin)

// SCREEN PARAMETERS ===================================================================================-

Adafruit_SSD1306 Display(128, 64); //define for the screen

typedef struct {
String hoverLabel; 
uint8_t x; 
uint8_t y; 

} hover;

const hover hoverOver[13] {
  
{"Back", 1, 54}, 
{"DPS:", 1, 15}, 
{"Motor:", 1, 23},
{"Brake:", 1, 31},
{"Hang:", 1, 39},
{"Comp:", 75, 15},
{"Mode:", 75, 23},
{"BSize:", 75, 31},
{"Save", 105, 54},
{"Forward", 25, 15},
{"Middle", 25, 25},
{"Rear", 25, 35},
{"Back", 52, 54}

};

char wordGuys[6] = {'N', 'Y', 'S', 'B', 'A', 'b'};  // Non numerical display for tournament mode and fire mode.


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
    wdt_reset();   // Continously reset watchdog to avoid reset. 
    if(BUTTONHIGH) {
      return;  
    }
  } 
}

void display_init() {         // Initializes screen, displays splash.
  Display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  Display.clearDisplay();
  Display.display();
  Display.setCursor(0, 0);
  Display.setTextColor(0); //black text for boot screen;
  Display.setTextSize(1);
  Display.setTextWrap(false);
  Display.clearDisplay();
  Display.drawBitmap(0, 0, splash, 128, 64, 1);

  Display.setCursor(5,37);  //splash screen text
  Display.println("0.9.0"); // Revision #
  Display.setCursor(5, 47);
  Display.println("WAHOO");
  Display.setCursor(5, 55);
  Display.println("Industries");
  Display.display();
}

// MAIN MENU ----------------------------------------------------------

void mainScreen(){

  Display.clearDisplay();
  Display.setTextSize(1);
  Display.setTextColor(WHITE); // White. 

  Display.setCursor(42, 0);
  Display.print("Spitfire");
  Display.setCursor(0, 55);
  Display.print("Beta0.9.0");
  Display.setCursor(123, 0); //just the V for the voltage
  Display.print("V"); //BETA add the actual values to print
  Display.setCursor(111 - ((menuState.length() - 3) * 6), 55);  // Keep "Forward", "Middle", "Rear", as far right as possible. 
  Display.print(menuState); 
  Display.setCursor(0, 15);
  Display.print("DPS:   ");
  Display.println(dpsSetting);
  Display.print("Motor: ");
  Display.print((motorspeedSetting - 1000) / 10);
  Display.println("%");
  Display.print("Brake: ");
  Display.println(brakeamountSetting);
  Display.print("Hang:  ");
  Display.print(hangtimeSetting);
  Display.println("ms");
  Display.setCursor(75, 15); 
  Display.print("Comp: ");
  Display.print(wordGuys[compSetting]);   // Setting in memory mapped to letter in wordGuys array.
  Display.setCursor(75, 23);
  Display.print("Mode: ");
  Display.println(wordGuys[modeSetting]);
  if(modeSetting == 3) {
  Display.setCursor(75, 31); 
  Display.print("BSize: ");
  Display.print(burstSetting);
  }
  
  Display.display();
}


void settingScreen(int counterCopy) {   // Contains settings master menu, parameter menu, save menu.


// SETTINGS MASTER MENU --------------------------------------------------------------------------------
Display.clearDisplay(); 
  if(menuState == "Settings") {

  Display.setTextSize(1);
  Display.setTextColor(WHITE); //white 
  Display.setCursor(40, 0);           //  Static labels.
  Display.print("Settings");
  Display.setCursor(0, 15);
  Display.print("DPS:   ");
  Display.println(dpsSetting);
  Display.print("Motor: ");
  Display.print(motorspeedSetting);
  Display.println("%");
  Display.print("Brake: ");
  
  Display.println(brakeamountSetting);
  Display.print("Hang:  ");
  Display.print(hangtimeSetting);
  Display.println("ms");
  Display.setCursor(75, 15); 
  Display.print("Comp:  ");
  Display.print(wordGuys[compSetting]);
  Display.setCursor(75, 23); 
  Display.print("Mode:  ");
  Display.print(wordGuys[modeSetting]);
  if(modeSetting == 3) {
  Display.setCursor(75, 31); 
  Display.print("BSize: ");
  Display.print(burstSetting);
  }
  Display.setCursor(105, 54); 
  Display.println("Save");
  Display.setCursor(1, 54);
  Display.print("Back");              
  Display.setTextColor(BLACK, WHITE); 

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
  if(menuState == "Comp:" || menuState == "Mode:") {
    Display.print(wordGuys[counterCopy]);                     // Display chracters instead of counter # depending counter.
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
  Display.setCursor(25, 15);
  Display.print(hoverOver[9].hoverLabel);
  Display.setCursor(25, 25);
  Display.print(hoverOver[10].hoverLabel);
  Display.setCursor(25, 35);
  Display.print(hoverOver[11].hoverLabel);
  Display.setCursor(52, 54);
  Display.print(hoverOver[12].hoverLabel);

  Display.fillRect(81, 15, 9, 8, 1);
  Display.drawRect(89, 15, 9, 8, 1);
  Display.drawRect(97, 15, 9, 8, 1);
  
  Display.drawRect(81, 25, 9, 8, 1);
  Display.fillRect(89, 25, 9, 8, 1);
  Display.drawRect(97, 25, 9, 8, 1);

  Display.drawRect(81, 35, 9, 8, 1);
  Display.drawRect(89, 35, 9, 8, 1);
  Display.fillRect(97, 35, 9, 8, 1);

  Display.setTextColor(BLACK, WHITE); 

  Display.setCursor(hoverOver[counterCopy].x, hoverOver[counterCopy].y); 
  Display.print(hoverOver[counterCopy].hoverLabel); 

  Display.display();
  return; 
  }
 }

// END OF settingScreen.

void setCounter(int counterCopy, uint8_t counterGhostCopy) {                //Setting upper and lower bound of counter depending on menu, set menuState.

menuState = hoverOver[counterCopy].hoverLabel;                              // Cheap way to keep menuState, correspond counter to index in hoverLabel, EX hoverOver[1].hoverLabel = "DPS:". 
  switch(counterCopy) {
    case SET:                            // Settings Menu. SET = 20
     lowerBound = 0; 
     upperBound = 8;
     menuState = "Settings";           // manually set to "Settings".
     counter = counterGhostCopy;       // Reset at chosen parameter.
      break;
    case 1:   // DPS.
     lowerBound = 1;                  // Set upper and lower bound for given parameter menu, DPS can be selected from 1 - 10.
     upperBound = 10;
     counter = dpsSetting;            // Once a parameter menu is displayed, set counter to value to current (parametername)Setting
     break; 
   case 2:   // MotorSpeed.
     lowerBound = 1; 
     upperBound = 100;
     counter = motorspeedSetting; 
     break;
   case 3:  // Brake. 
     lowerBound = 1; 
     upperBound = 3;
     counter = brakeamountSetting; 
     break;
  case 4:   // Hangtime.
     lowerBound = 0; 
     upperBound = 4000; 
     counter = hangtimeSetting; 
     break;
  case 5:   // Tournament Mode.
     lowerBound = 0; 
     upperBound = 1;
     counter = compSetting; 
     break; 
  case 6:   // Fire Mode.
     lowerBound = 2; 
     upperBound = 5; 
     counter = modeSetting; 
     break; 
  case 7:  
     lowerBound = 2; 
     upperBound = 5;
     counter = burstSetting; 
     break;
  case 8: 
     lowerBound = 9; 
     upperBound = 12;
     counter = 9; 
     break;
  }
    return; 
}

void saveenteredValue(uint8_t counterGhostCopy, int counterCopy) {      // Save parameter value according to current screen. 

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


void rebootingScreen(){         // Called when rebooting.
  Display.clearDisplay();
  Display.setTextSize(2);
  Display.setTextColor(1); 
  Display.setCursor(10, 25);
  Display.print("Rebooting...");
  Display.display();
}

void lowbatteryScreen() {
  Display.clearDisplay();
  Display.setTextSize(1);
  Display.setTextColor(1); 
  Display.setCursor(16, 18);
  Display.println("Voltage too low:");
  Display.setCursor(16, 26);
  Display.println("Replace battery.");
  Display.display();
}


void settingsMenu() {          // Master settings menu master function, calls previous functions to update screen according to counter and menuState values, detects button press and encoder scrolls.

  // On function call in loop().
  waitHigh(); 
  motorspeedSetting = (motorspeedSetting - 1000) / 10;
  setCounter(SET, counterGhost); 
  settingScreen(counter);


  while(1) {                              // Runs until broken from via back button or save button. 
  
   wdt_reset();                           // Continously reset watchdog to avoid reset.
   currentStateCLK = CLOCKCHECK; 

    if(currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
		  // If the DT state is different than the CLK state then the encoder is rotating CCW so decrement.
		  if (DTCHECK != currentStateCLK) {
        if(counter < upperBound) {
			  (menuState == "Hang:") ? counter += 100 : counter++;     // If on hang, increment/decrement by 100, otherwise, increment by 1. 
        (menuState == "Settings" && modeSetting != 3 && counter == 7) ? counter = 8 : counter += 0;
        }
		  } else {
        if(counter > lowerBound) {
			  (menuState == "Hang:") ? counter -= 100 : counter--; 
        (menuState == "Settings" && modeSetting != 3 && counter == 7) ? counter = 6 : counter -= 0; 
       }
		  }  
      settingScreen(counter);
	}

  lastStateCLK = currentStateCLK;     


	if (!BUTTONHIGH) {

    if (millis() - lastButtonPress > 50 && menuState == "Settings" && counter == 0) { // If back button pressed, break from settings menu, return to void loop()
      waitHigh();
      counter = 1; 
      counterGhost = counter;  
      menuState = "Main Menu"; 
      break; 
    }
    if (millis() - lastButtonPress > 50 && menuState == "Save" && counter != 12) {     // If save button confirmed (Pressed on anything other than '9' (back button), break from settings menu, return to void loop()
      waitHigh();
      rebootingScreen();
      break;                                                                        
		}
    if (millis() - lastButtonPress > 50 && menuState != "Settings") {      // If in any other menu than master settings page, return to it.
      waitHigh();
      saveenteredValue(counterGhost, counter);                                          // Save value entered according to counterGhost and current value of counter.
      setCounter(SET, counterGhost);                                                    // Return to master settings menu settings. lmao
      settingScreen(counter);                                            
      continue;                                                                         // Return to beginning of for loop to avoid chain if statement
		}
    if (millis() - lastButtonPress > 50 && menuState == "Settings") {                   // Send counter position to determine which parameter menu to display, EX: 
      waitHigh();
      counterGhost = counter;                                                           // Remember which parameter was selected
      setCounter(counter, counterGhost);                                                // Send position of counter to determine upper and lower bound, as well as new menuState.
      settingScreen(counter);                                                           // Send value of counter to determine which parameter menu to display, counter corresponds to index. 
		}
		// Remember last button press event
		lastButtonPress = millis();
	}
	// Put in a slight delay to help debounce the reading
	delay(1);
 }
 
  return; 
}