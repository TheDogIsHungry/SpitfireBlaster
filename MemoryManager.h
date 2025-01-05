
// LIBRARIES  =========================================

#include <EEPROM.h>       // For AVR, SAMD boards use: FlashStorage_SAMD

// DEFINES =========================================

#define dps_for 1        
#define dps_mid 2        
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
int brakeamountSetting; 
int hangtimeSetting;      // Time before motor stops after trigger release, in ms.
uint8_t compSetting;      // Tournament mode ON or OFF (Y or N).
uint8_t modeSetting;      // Fire mode, 4 options: Single (S), Burst (B), Auto (A), binary (b).
uint8_t burstSetting; 
String menuState = "Main Menu"; // Contains menustate at any given point. In main menu, display switch position, in settings menu, hold setting menu state. 

// FUNCTIONS =========================================

void loadvalues() {   // Since this is called in void loop() repeatedly, use direct port checks, digitalRead() calls up to 5 functions, and contains 3 if statements, this is faster.
            
  if (!SWITCHPOS_1 && SWITCHPOS_2) {      // Forward
    dpsSetting = EEPROM.read(dps_for);  
    motorspeedSetting = (EEPROM.read(mspeed_for) * 10) + 1000;        // Prefer to use math to create equivalent value, rather than using 2 bytes for values above 255.
    brakeamountSetting = EEPROM.read(bam_for);
    hangtimeSetting = EEPROM.read(hang_for) * 100;  
    compSetting = EEPROM.read(comp_for); 
    modeSetting = EEPROM.read(mode_for); 
    burstSetting = EEPROM.read(burst_for); 
    menuState = "Forward"; 
    return;
  } else if (SWITCHPOS_1 && SWITCHPOS_2) {  // Middle
    dpsSetting = EEPROM.read(dps_mid); 
    motorspeedSetting = (EEPROM.read(mspeed_mid) * 10) + 1000;   
    brakeamountSetting = EEPROM.read(bam_mid);
    hangtimeSetting = EEPROM.read(hang_mid) * 100; 
    compSetting = EEPROM.read(comp_mid); 
    modeSetting = EEPROM.read(mode_mid); 
    burstSetting = EEPROM.read(burst_mid); 
    menuState = "Middle"; 
    return;
  } else if (SWITCHPOS_1 && !SWITCHPOS_2) { // Rear
    dpsSetting = EEPROM.read(dps_rear);
    motorspeedSetting = (EEPROM.read(mspeed_rear) * 10) + 1000;     
    brakeamountSetting = EEPROM.read(bam_rear);
    hangtimeSetting = EEPROM.read(hang_rear) * 100; 
    compSetting = EEPROM.read(comp_rear); 
    modeSetting = EEPROM.read(mode_rear); 
    burstSetting = EEPROM.read(burst_rear); 
    menuState = "Rear"; 
    return; 
  }
 }


void savevalues(int savePosition) {    // Save all inputted values entered from screen to EEPROM, reset blaster. 

  switch(savePosition) {               // Passed position determines which switch to update to, update() as opposed to write() to prevent rewrites of identical data.
    case 9:
    EEPROM.update(dps_for, dpsSetting);
    EEPROM.update(mspeed_for, motorspeedSetting); 
    EEPROM.update(bam_for, brakeamountSetting); 
    EEPROM.update(hang_for, (hangtimeSetting / 100));
    EEPROM.update(comp_for, compSetting); 
    EEPROM.update(mode_for, modeSetting); 
    EEPROM.update(burst_for, burstSetting);
    break;
    case 10:
    EEPROM.update(dps_mid, dpsSetting);
    EEPROM.update(mspeed_mid, motorspeedSetting); 
    EEPROM.update(bam_mid, brakeamountSetting); 
    EEPROM.update(hang_mid, (hangtimeSetting / 100));
    EEPROM.update(comp_mid, compSetting); 
    EEPROM.update(mode_mid, modeSetting);
    EEPROM.update(burst_mid, burstSetting);
    break;
    case 11:
    EEPROM.update(dps_rear, dpsSetting);
    EEPROM.update(mspeed_rear, motorspeedSetting); 
    EEPROM.update(bam_rear, brakeamountSetting); 
    EEPROM.update(hang_rear, (hangtimeSetting / 100));
    EEPROM.update(comp_rear, compSetting); 
    EEPROM.update(mode_rear, modeSetting);
    EEPROM.update(burst_rear, burstSetting);
    break;
  }
//delay(10000); // Wait for watchdog to reset microcontroller.
}




