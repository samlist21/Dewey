#include "Arduino.h"
#include "def.h"


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
