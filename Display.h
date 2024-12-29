
// LIBRARIES ==========================================================================================

#include "Adafruit_SSD1306.h" //screen 
#include "Splash.h" 
#include "MemoryManager.h"    // EEPROM functions.

// PINS ===============================================================================================

#define clockPin 7
#define dtPin 8
#define buttonPin 9
#define SET 20 // not a pin

// SCREEN PARAMETERS ===================================================================================

Adafruit_SSD1306 Display(128, 64); //define for the screen

uint16_t counter;                 // Incremented / decremented to define where user is hovering (what to highlight), as well as what value to select.
uint8_t counterGhost;             // When entering paramter menu, "Motor" for example, which indexed at 2, remember this position to return to it in master settings screen.
uint8_t lowerBound;               // Defines lower bound for menus, 0 - 7 in master settings menu encompasses 'Back' to 'Save', 0 - 4000 for hang setting, etc. 
uint16_t upperBound;              // Defines upperbound of what was explained above.
char wordGuys[6] = {'N', 'Y', 'S', 'B', 'A', 'b'};  // Non numerical display for tournament mode and fire mode. 
uint8_t currentStateCLK;          
uint8_t lastStateCLK;             
uint8_t btnState;                 // State of rotary encoder button, HIGH or LOW.
unsigned long lastButtonPress = 0;  // Takes timestamp of button press using millis()

// FUNCTIONS ============================================================================================

int counterLength(int i) {    // Function to do some math to center labels and numbers properly depending on length, 1 = 1, "Hi" = 2, 500 = 3 etc. 
 if (i == 0) {return 1;} 
    return log10(i) + 1;
}

float voltageRead() {
  return ((analogRead(A7)) * (5.0 / 1023.0)) * ((10000.0 + 4300.0) / 4300.0); 
}


void waitHigh() {             // After button press, wait for it to be depressed to avoid chaining if statements. 
  while(1) {
    wdt_reset();   // Continously reset watchdog to avoid reset.
    btnState = digitalRead(buttonPin);  
    if(btnState == HIGH) {
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
  Display.setCursor(89, 0);  //BETA 88 maybe wokwi offset by 1
  Display.print(voltageRead());
  Display.print("V");
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
  Display.print(wordGuys[modeSetting]);

  
  Display.display();
}


void settingScreen(int counterCopy) {   // Contains settings master menu, parameter menu, save menu.

// SETTINGS MASTER MENU ----------------------------------------------

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
  Display.print("Comp: ");
  Display.print(wordGuys[compSetting]);
  Display.setCursor(75, 23); 
  Display.print("Mode: ");
  Display.print(wordGuys[modeSetting]);
  //Display.fillRect(95, 54, 30, 30, BLACK); 
  Display.setCursor(105, 54); 
  Display.println("Save");
  Display.setCursor(1, 54);
  Display.print("Back");              
  Display.setTextColor(BLACK, WHITE); 

  switch(counterCopy) { //  Dynamic labels, depending on counter state in settings menu, display highlight over parameter, arrays did not work, I tried!!!!!
    case 0:
    Display.setCursor(1, 54);
    Display.print("Back");
    break;
    case 1:
    Display.setCursor(1, 15);
    Display.print("DPS:  ");
    break; 
    case 2:
    Display.setCursor(1, 23);
    Display.print("Motor: ");  
    break;
    case 3: 
    Display.setCursor(1, 31);
    Display.print("Brake: ");
    break;
    case 4:
    Display.setCursor(1, 39);
    Display.print("Hang: ");
    break; 
    case 5:
    Display.setCursor(75, 15);
    Display.print("Comp: ");
    break; 
    case 6:
    Display.setCursor(75, 23);
    Display.print("Mode: ");
    break; 
    case 7:
    Display.setCursor(105, 54);
    Display.print("Save");
    break;
  }
  Display.display();
  return; 
}

// PARAMETER MENUS ------------------------------------------------------------------------------------

if(menuState != "Settings" && menuState != "Save") {     // When entering parameter menus, display accordingly. 
  Display.setTextSize(2);
  Display.setTextColor(1); //white
  Display.setCursor(52 - ((menuState.length() - 2) * 6), 0);    // Aforementioned math to center numbers and labels, one digit or character is ~ 6 pixels. Start at 3 for label DPS as reference
  Display.print(menuState);
  Display.setCursor(64 - (counterLength(counterCopy) * 6), 24); // Start at 1 for single digit. Each subsequent digit or character subtracts another 6, to keep centered.
  if(menuState == "Comp" || menuState == "Mode") {
    Display.print(wordGuys[counterCopy]);                     // Display chracters instead of counter # depending counter.
  }
  else {
  Display.print(counterCopy);                                // All other parameters are numerical.
  }
  Display.fillRect(50, 54, 100, 10, BLACK); //BETA fix for artifacts in the bottom right (WORKING)!
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
  Display.print("Forward");
  Display.setCursor(25, 25);
  Display.print("Middle");
  Display.setCursor(25, 35);
  Display.print("Rear");
  Display.setCursor(52, 54);
  Display.print("Back");

  
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
  switch(counterCopy) {
    case 0:
    Display.setCursor(52, 54);
    Display.print("Back");
    break;
    case 1:
    Display.setCursor(25, 35);
    Display.print("Rear");
    break;
    case 2:
    Display.setCursor(25, 25);
    Display.print("Middle");
    break;
    case 3:
    Display.setCursor(25, 15);
    Display.print("Forward");
    break; 
   }
  Display.display();
  return; 
  }
 }

// END OF settingScreen.

void setCounter(int i) {                //Setting upper and lower bound of counter depending on menu, set menuState.
  switch(i) {
    case 20:                            // Settings Menu. SET = 20
     lowerBound = 0; // Back.
     upperBound = 7; 
     menuState = "Settings"; 
     counter = counterGhost;  // Reset at previous highlighted setting.
      break;
    case 1:   // DPS.
     lowerBound = 1; 
     upperBound = 10;
     menuState = "DPS";   
     counter = dpsSetting; 
     break; 
   case 2:   // MotorSpeed.
     lowerBound = 1; 
     upperBound = 100;
     menuState = "Motor"; 
     counter = motorspeedSetting; 
     break;
   case 3:  // Brake. 
     lowerBound = 1; 
     upperBound = 3;
     menuState = "Brake"; 
     counter = brakeamountSetting; 
     break;
  case 4:   // Hangtime.
     lowerBound = 0; 
     upperBound = 4000;
     menuState = "Hang"; 
     counter = hangtimeSetting; 
     break;
  case 5:   // Tournament Mode.
     lowerBound = 0; 
     upperBound = 1;
     menuState = "Comp"; 
     counter = compSetting; 
     break; 
  case 6:   // Fire Mode.
     lowerBound = 2; 
     upperBound = 5;
     menuState = "Mode"; 
     counter = modeSetting; 
     break; 
  case 7:   // Save.
     lowerBound = 0; 
     upperBound = 3;
     menuState = "Save"; 
     counter = 3; 
     break;
  }
 
  return; 
}

void saveenteredValue(int counterCopy) {      // Save parameter value according to current screen. 

if(menuState == "DPS") {
  dpsSetting = counterCopy; 
}
if(menuState == "Motor") {
  motorspeedSetting = counterCopy;  
}
if(menuState == "Brake") {
  brakeamountSetting = counterCopy; 
}
if(menuState == "Hang") {
  hangtimeSetting = counterCopy;
}
if(menuState == "Comp") {
  compSetting = counterCopy;
}
if(menuState == "Mode") {
  modeSetting = counterCopy; 
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


void settingsMenu() {          // Master settings menu master function, calls previous functions to update screen according to counter and menuState values, detects button press and encoder scrolls.

  // On function call in loop().
  waitHigh(); 
  motorspeedSetting = (motorspeedSetting - 1000) / 10;
  counter = 1; 
  counterGhost = counter; 
  setCounter(SET); 
  Display.clearDisplay(); 
  settingScreen(counter);


  while(1) {                              // Runs until broken from via back button or save button. 
  
    wdt_reset();                           // Continously reset watchdog to avoid reset.
    currentStateCLK = digitalRead(clockPin);  // Read clockpin for scroll data.

    if(currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
		  // If the DT state is different than the CLK state then the encoder is rotating CCW so decrement.
		  if (digitalRead(dtPin) != currentStateCLK) {
        if(counter < upperBound) {
			  (menuState == "Hang") ? counter += 100 : counter++;     // If on hang, increment/decrement by 100, otherwise, increment by 1. 
        }
		  } else {
        if(counter > lowerBound) {
			  (menuState == "Hang") ? counter -= 100 : counter--; 
       }
		  }  
      /*
		  Serial.print("Mode: ");
		  Serial.print(menuState);
		  Serial.print(" | Counter: ");
		  Serial.println(counter);
      */
      Display.clearDisplay(); 
      settingScreen(counter);
      
	}

  lastStateCLK = currentStateCLK;     
	// Read the button state
	btnState = digitalRead(buttonPin);      // Read button pin

	if (btnState == LOW) {

    if (millis() - lastButtonPress > 50 && menuState == "Settings" && counter == 0) { // If back button pressed, break from settings menu, return to void loop()
      waitHigh(); 
      menuState = "Main Menu"; 
      break; 
    }
    if (millis() - lastButtonPress > 50 && menuState == "Save" && counter != 0) {     // If save button confirmed, break from settings menu, return to void loop()
      waitHigh();
      //Serial.print("Reset..."); 
      rebootingScreen();
      break;                                                                        
		}
    if (millis() - lastButtonPress > 50 && menuState != "Settings") {      // If in any other menu than master settings page, return to it.
      waitHigh();
      saveenteredValue(counter);                                          // Save value entered.
      setCounter(SET);                                                    // Return to master settings menu settings. lmao
      Display.clearDisplay(); 
      settingScreen(counter);                                            
      continue;                                                           // return to beginning of for loop to avoid chain if statement
		}
    if (millis() - lastButtonPress > 50 && menuState == "Settings") {     // Send counter position to determine which menu to display.
      waitHigh();
      counterGhost = counter;      
      setCounter(counter);
      Display.clearDisplay(); 
      settingScreen(counter); 
		}
		// Remember last button press event
		lastButtonPress = millis();
	}
	// Put in a slight delay to help debounce the reading
	delay(1);
 }
  return; 
}
