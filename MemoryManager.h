
// LIBRARIES  =========================================

#include <EEPROM.h>       // For AVR, SAMD boards use: FlashStorage_SAMD. Works with Pi pico via arduino-pico core, must call EEPROM.begin() and commit(). 

// DEFINES =========================================

#define dps_for 1        // Every switch position has its own set of values, for: forward, middle, rear.
#define dps_mid 2        // Define defines memory address position, each value gets one byte, total is 21 bytes of EEPROM. 
#define dps_rear 3

#define mspeed_for 4
#define mspeed_mid 5
#define mspeed_rear 6

#define bam_for 7
#define bam_mid 8
#define bam_rear 9

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

#define switch_pin_1 4
#define switch_pin_2 5
#define SWITCHPOS_1 digitalRead(switch_pin_1)
#define SWITCHPOS_2 digitalRead(switch_pin_2)


// CONFIGURATION PARAMETERS =========================================

uint8_t dpsSetting;  // Rate of fire in darts per second.
int motorspeedSetting;  // Speed of motor, 1000 - 2000.
int brakeamountSetting; // Brake amount, used as # with values 1 through 3, the higher the number the faster the motors will break.
int hangtimeSetting;      // Time before motor revs down after trigger release, in ms.
uint8_t compSetting;      // Tournament mode On or Off
uint8_t modeSetting;      // Fire mode, 4 options: Single (Semi), Burst (Bst), Auto (Auto), Binary (Bin).
uint8_t burstSetting;     // Contains burst amount, 2 - 5 darts per trigger pull.
String menuState = "Main Menu"; // Contains menustate at any given point. In main menu, display switch position, in settings menu, hold setting menu state. 
String profileSwitch = "";  
// FUNCTIONS =========================================

void loadvalues() {   
            
  if (!SWITCHPOS_1 && SWITCHPOS_2) {      // Forward
    dpsSetting = EEPROM.read(dps_for);  
    motorspeedSetting = (EEPROM.read(mspeed_for) * 10) + 1000;        // Prefer to use math to create equivalent value, rather than using 2 bytes for values above 255.
    brakeamountSetting = EEPROM.read(bam_for);
    hangtimeSetting = EEPROM.read(hang_for) * 100;  
    compSetting = EEPROM.read(comp_for); 
    modeSetting = EEPROM.read(mode_for); 
    burstSetting = EEPROM.read(burst_for); 
    profileSwitch = "Forward"; 
    return;
  } else if (SWITCHPOS_1 && SWITCHPOS_2) {  // Middle
    dpsSetting = EEPROM.read(dps_mid); 
    motorspeedSetting = (EEPROM.read(mspeed_mid) * 10) + 1000;   
    brakeamountSetting = EEPROM.read(bam_mid);
    hangtimeSetting = EEPROM.read(hang_mid) * 100; 
    compSetting = EEPROM.read(comp_mid); 
    modeSetting = EEPROM.read(mode_mid); 
    burstSetting = EEPROM.read(burst_mid); 
    profileSwitch = "Middle"; 
    return;
  } else if (SWITCHPOS_1 && !SWITCHPOS_2) { // Rear
    dpsSetting = EEPROM.read(dps_rear);
    motorspeedSetting = (EEPROM.read(mspeed_rear) * 10) + 1000;     
    brakeamountSetting = EEPROM.read(bam_rear);
    hangtimeSetting = EEPROM.read(hang_rear) * 100; 
    compSetting = EEPROM.read(comp_rear); 
    modeSetting = EEPROM.read(mode_rear); 
    burstSetting = EEPROM.read(burst_rear); 
    profileSwitch = "Rear"; 
    return; 
  }
 }


void savevalues(int savePosition) {    // Save all inputted values entered from screen to EEPROM. 

  switch(savePosition) {               // Passed position determines which switch position to update to, update() as opposed to write() to prevent rewrites of identical data.
    case 9:                                                // Forward 
    EEPROM.update(dps_for, dpsSetting);
    EEPROM.update(mspeed_for, motorspeedSetting); 
    EEPROM.update(bam_for, brakeamountSetting); 
    EEPROM.update(hang_for, (hangtimeSetting / 100));
    EEPROM.update(comp_for, compSetting); 
    EEPROM.update(mode_for, modeSetting); 
    EEPROM.update(burst_for, burstSetting);
    break;
    case 10:                                               // Middle
    EEPROM.update(dps_mid, dpsSetting);
    EEPROM.update(mspeed_mid, motorspeedSetting); 
    EEPROM.update(bam_mid, brakeamountSetting); 
    EEPROM.update(hang_mid, (hangtimeSetting / 100));
    EEPROM.update(comp_mid, compSetting); 
    EEPROM.update(mode_mid, modeSetting);
    EEPROM.update(burst_mid, burstSetting);
    break;
    case 11:                                              // Rear
    EEPROM.update(dps_rear, dpsSetting);
    EEPROM.update(mspeed_rear, motorspeedSetting); 
    EEPROM.update(bam_rear, brakeamountSetting); 
    EEPROM.update(hang_rear, (hangtimeSetting / 100));
    EEPROM.update(comp_rear, compSetting); 
    EEPROM.update(mode_rear, modeSetting);
    EEPROM.update(burst_rear, burstSetting);
    break;
  }
EEPROM.commit(); 
delay(200);
rp2040.reboot(); 
}




