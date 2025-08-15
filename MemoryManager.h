
// LIBRARIES  =========================================

#include <EEPROM.h>       // For AVR, SAMD boards use: FlashStorage_SAMD. Works with Pi pico via arduino-pico core, must call EEPROM.begin() and commit(). 

// DEFINES =========================================

#define dps_for 1        // Every switch position has its own set of values, for: forward, middle, rear.
#define dps_mid 2        // Define defines memory address position, each value gets one byte, total is 21 bytes of EEPROM. 
#define dps_rear 3

#define mspeed_for 4
#define mspeed_mid 5
#define mspeed_rear 6

#define trace_for 7
#define trace_mid 8
#define trace_rear 9

#define hang_for 10
#define hang_mid 11
#define hang_rear 12

#define comp_for 13
#define comp_mid 14
#define comp_rear 15

#define mode_for 16
#define mode_mid 17
#define mode_rear 18

#define burst_for 19
#define burst_mid 20
#define burst_rear 21


// CONFIGURATION PARAMETERS =========================================

int dpsSetting;              // Rate of fire in darts per second.
int motorspeedSetting;           // Speed of motor, 1000 - 2000.
int tracerSetting;           // Brake amount, used as # with values 1 through 3, the higher the number the faster the motors will break.
int hangtimeSetting;             // Time before motor revs down after trigger release, in ms.
int compSetting;             // Tournament mode On or Off
int modeSetting;             // Fire mode, 4 options: Single (Semi), Burst (Bst), Auto (Auto), Binary (Bin).
int burstSetting;            // Contains burst amount, 2 - 5 darts per trigger pull.
String menuState = "Main Menu";  // Contains menustate at any given point, for settings menu and main menu.
String profileSwitch = "";       // String to display current switch position, forward, middle, rear.

int* modifierArray[7] = { &dpsSetting, &motorspeedSetting, &tracerSetting, &hangtimeSetting, &compSetting, &modeSetting, &burstSetting };  // Array of pointers to modify values in the settings menu.

// FUNCTIONS =========================================

void loadvalues(uint8_t loadPosition) {   
 
  switch(loadPosition) {
    case 0:
    dpsSetting = EEPROM.read(dps_for);  
    motorspeedSetting = EEPROM.read(mspeed_for);   // Prefer to use math to create equivalent value, rather than using 2 bytes for values above 255.
    tracerSetting = EEPROM.read(trace_for);
    hangtimeSetting = EEPROM.read(hang_for) * 100;  
    compSetting = EEPROM.read(comp_for); 
    modeSetting = EEPROM.read(mode_for); 
    burstSetting = EEPROM.read(burst_for); 
    profileSwitch = "Front"; 
    break;
    case 1:
    dpsSetting = EEPROM.read(dps_mid); 
    motorspeedSetting = EEPROM.read(mspeed_mid);   
    tracerSetting = EEPROM.read(trace_mid);
    hangtimeSetting = EEPROM.read(hang_mid) * 100; 
    compSetting = EEPROM.read(comp_mid); 
    modeSetting = EEPROM.read(mode_mid); 
    burstSetting = EEPROM.read(burst_mid); 
    profileSwitch = "Middle"; 
    break;
    case 2:
    dpsSetting = EEPROM.read(dps_rear);
    motorspeedSetting = EEPROM.read(mspeed_rear);     
    tracerSetting = EEPROM.read(trace_rear);
    hangtimeSetting = EEPROM.read(hang_rear) * 100; 
    compSetting = EEPROM.read(comp_rear); 
    modeSetting = EEPROM.read(mode_rear); 
    burstSetting = EEPROM.read(burst_rear); 
    profileSwitch = "Rear"; 
    break; 
  }
 }


void savevalues(int savePosition) { 
               
  switch(savePosition) {                               // Passed position determines which switch position to update to, EEPROM.update causes erratic behaviour as entire flash sector needs to be reset.
    case 9:                                            // Forward 
    EEPROM.write(dps_for, dpsSetting);
    EEPROM.write(mspeed_for, motorspeedSetting); 
    EEPROM.write(trace_for, tracerSetting); 
    EEPROM.write(hang_for, (hangtimeSetting / 100));
    EEPROM.write(comp_for, compSetting); 
    EEPROM.write(mode_for, modeSetting); 
    EEPROM.write(burst_for, burstSetting); 
    break;
    case 10:                                           // Middle
    EEPROM.write(dps_mid, dpsSetting);
    EEPROM.write(mspeed_mid, motorspeedSetting); 
    EEPROM.write(trace_mid, tracerSetting); 
    EEPROM.write(hang_mid, (hangtimeSetting / 100));
    EEPROM.write(comp_mid, compSetting); 
    EEPROM.write(mode_mid, modeSetting);
    EEPROM.write(burst_mid, burstSetting);
    break;
    case 11:                                           // Rear
    EEPROM.write(dps_rear, dpsSetting);
    EEPROM.write(mspeed_rear, motorspeedSetting); 
    EEPROM.write(trace_rear, tracerSetting); 
    EEPROM.write(hang_rear, (hangtimeSetting / 100));
    EEPROM.write(comp_rear, compSetting); 
    EEPROM.write(mode_rear, modeSetting);
    EEPROM.write(burst_rear, burstSetting);
    break;
  }
EEPROM.commit();
delay(100);
}
