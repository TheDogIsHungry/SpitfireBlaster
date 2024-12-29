
// LIBRARIES  =========================================

#include <EEPROM.h>       // For AVR, SAMD boards use: FlashStorage_SAMD

// DEFINES =========================================

#define dps_for 30        // Every switch position has its own set of values, for: forward, middle, rear.
#define dps_mid 31        // Define defines memory address position, each value gets one byte, total is 18 bytes of EEPROM. 
#define dps_rear 32

#define mspeed_for 33
#define mspeed_mid 34
#define mspeed_rear 35

#define bam_for 36
#define bam_mid 37
#define bam_rear 38

#define hang_for 39
#define hang_mid 40
#define hang_rear 41

#define comp_for 42
#define comp_mid 43
#define comp_rear 44

#define mode_for 45
#define mode_mid 46
#define mode_rear 47

#define switch_pos_1 4 // Pins for 3 position switch, to determine which set of values to load.
#define switch_pos_2 5


// CONFIGURATION PARAMETERS =========================================

int dpsSetting;  // Rate of fire in darts per second.
int motorspeedSetting;  // Speed of motor, 1000 - 2000.
int brakeamountSetting; 
int hangtimeSetting;  // Time before motor stops after trigger release, in ms.
int compSetting;      // Tournament mode ON or OFF (Y or N).
int modeSetting;      // Fire mode, 4 options: Single (S), Burst (B), Auto (A), binary (b).
String menuState = "Main Menu"; // Contains menustate at any given point. In main menu, display switch position, in settings menu, hold setting menu state. 

// FUNCTIONS =========================================

void loadvalues() {   // Since this is called in void loop() repeatedly, use direct port checks, digitalRead() calls up to 5 functions, and contains 3 if statements, this is faster.
            
  if ((PIND & (1 << switch_pos_1)) != 0 && (PIND & (1 << switch_pos_2)) == 0) {      // Forward
    dpsSetting = EEPROM.read(dps_for);  
    motorspeedSetting = (EEPROM.read(mspeed_for) * 10) + 1000;        // Prefer to use math to create equivalent value, rather than using 2 bytes for values above 255.
    brakeamountSetting = EEPROM.read(bam_for);
    hangtimeSetting = EEPROM.read(hang_for) * 100;  
    compSetting = EEPROM.read(comp_for); 
    modeSetting = EEPROM.read(mode_for); 
    menuState = "Forward"; 
    return;
  } else if ((PIND & (1 << switch_pos_1)) != 0 && (PIND & (1 << switch_pos_2)) != 0) {  // Middle
    dpsSetting = EEPROM.read(dps_mid); 
    motorspeedSetting = (EEPROM.read(mspeed_mid) * 10) + 1000;   
    brakeamountSetting = EEPROM.read(bam_mid);
    hangtimeSetting = EEPROM.read(hang_mid) * 100; 
    compSetting = EEPROM.read(comp_mid); 
    modeSetting = EEPROM.read(mode_mid); 
    menuState = "Middle"; 
    return;
  } else if ((PIND & (1 << switch_pos_1)) == 0 && (PIND & (1 << switch_pos_2)) != 0) { // Rear
    dpsSetting = EEPROM.read(dps_rear);
    motorspeedSetting = (EEPROM.read(mspeed_rear) * 10) + 1000;     
    brakeamountSetting = EEPROM.read(bam_rear);
    hangtimeSetting = EEPROM.read(hang_rear) * 100; 
    compSetting = EEPROM.read(comp_rear); 
    modeSetting = EEPROM.read(mode_rear); 
    menuState = "Rear"; 
    return; 
  }
}


void savevalues(int savePosition) {    // Save all inputted values entered from screen to EEPROM, reset blaster. 

  switch(savePosition) {               // Passed position determines which switch to update to, update() as opposed to write() to prevent rewrites of identical data.
    case 3:
    EEPROM.update(dps_for, dpsSetting);
    EEPROM.update(mspeed_for, motorspeedSetting); 
    EEPROM.update(bam_for, brakeamountSetting); 
    EEPROM.update(hang_for, (hangtimeSetting / 100));
    EEPROM.update(comp_for, compSetting); 
    EEPROM.update(mode_for, modeSetting); 
    break;
    case 2:
    EEPROM.update(dps_mid, dpsSetting);
    EEPROM.update(mspeed_mid, motorspeedSetting); 
    EEPROM.update(bam_mid, brakeamountSetting); 
    EEPROM.update(hang_mid, (hangtimeSetting / 100));
    EEPROM.update(comp_mid, compSetting); 
    EEPROM.update(mode_mid, modeSetting);
    break;
    case 1:
    EEPROM.update(dps_rear, dpsSetting);
    EEPROM.update(mspeed_rear, motorspeedSetting); 
    EEPROM.update(bam_rear, brakeamountSetting); 
    EEPROM.update(hang_rear, (hangtimeSetting / 100));
    EEPROM.update(comp_rear, compSetting); 
    EEPROM.update(mode_rear, modeSetting);
    break;
  }
delay(10000); // Wait for watchdog to reset microcontroller.
}




