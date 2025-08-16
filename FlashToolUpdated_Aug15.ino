#include <EEPROM.h>
#define dps_for 1        
#define dps_mid 2        
#define dps_rear 3

#define mspeed_for 4
#define mspeed_mid 5
#define mspeed_rear 6

#define brake_for 7
#define brake_mid 8
#define brake_rear 9

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

void setup(){
Serial.begin(9600); //start
pinMode(LED_BUILTIN, OUTPUT);
delay(2000);
Serial.println("Booted...");
EEPROM.begin(21); 

for(int i = 0; i < 15; i++){  //led flash
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(50);
}


if((EEPROM.read(dps_for)) != 5){  //to make sure that we dont double write
Serial.println("Status: Started");
Serial.println("[#                                 ]");
delay(500);


EEPROM.write(dps_for, 4); 
EEPROM.write(dps_mid, 6); 
EEPROM.write(dps_rear, 8); 
Serial.println("[########                          ]");
delay(500);

EEPROM.write(mspeed_for, 55); 
EEPROM.write(mspeed_mid, 60); 
EEPROM.write(mspeed_rear, 80); 
Serial.println("[#############                     ]");
delay(500);

EEPROM.write(brake_for, 2); 
EEPROM.write(brake_mid, 3); 
EEPROM.write(brake_rear, 4); 
Serial.println("[##################                ]");
delay(500);

EEPROM.write(hang_for, 20); 
EEPROM.write(hang_mid, 30); 
EEPROM.write(hang_rear, 40); 
Serial.println("[#######################           ]");
delay(500);

EEPROM.write(comp_for, 0); 
EEPROM.write(comp_mid, 1); 
EEPROM.write(comp_rear, 0); 
Serial.println("[############################      ]");
delay(500);

EEPROM.write(mode_for, 6); 
EEPROM.write(mode_mid, 7); 
EEPROM.write(mode_rear, 8); 
Serial.println("[################################  ]");
delay(500);

EEPROM.write(burst_for, 2); 
EEPROM.write(burst_mid, 4); 
EEPROM.write(burst_rear, 5); 
Serial.println("[##################################]");
delay(500);

EEPROM.commit();

Serial.println("Values loaded"); 
digitalWrite(LED_BUILTIN, HIGH);

delay(1400);

for(int i = 1; i < 22; i++) {
  Serial.println(EEPROM.read(i));
  delay(100);
}

}else if((EEPROM.read(dps_for)) == 4){
  Serial.print("already flashed");
  digitalWrite(LED_BUILTIN, HIGH);
  for(int i = 0; i < 3; i++){  //led flash
  digitalWrite(LED_BUILTIN, HIGH);
  delay(150);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(150);
}
  for(int i = 1; i < 22; i++) {
  Serial.println(EEPROM.read(i));
  delay(100);
}
}
}
void loop(){}
