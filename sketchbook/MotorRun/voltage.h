#include "Arduino.h"
#include "def.h"

unsigned long voltageMillis = millis();


void readVoltage(byte reading) {
  char floatStrCalc[10];
  char floatStrBus[10];
  int pin = 0; // 0 = Electroinics Voltage
  String name = "None";   //name of pin being addressed

  switch (reading) {
    case  ELECTRONICS :
      name = "Electronic ";
      break;
    case  MOTORS :
      name = "Motor ";
      break;
    case  PROCESSOR :
      name = "Processor ";
      break;
    default :
      name = "Unknown ";
      break;
  }

  int busCounts = analogRead(reading);
  float calcVoltage = busCounts / 41.322; // 24.75 / 1023 = .0242 = 1/41.322

  dtostrf(calcVoltage, 4, 2, floatStrCalc);

  Serial.print (name);
  Serial.println("Voltage=" + String(floatStrCalc) + " V");

}

void voltageCheck(){
  
  // Check voltage evry (50 * 250 s) or ~12.5 seconds
  if (millis() -voltageMillis > 10000) {
    
    voltageMillis = millis();
    readVoltage(ELECTRONICS);  // 0 is pin 0 for the Electronics - 1 will be for motors
    }
}
