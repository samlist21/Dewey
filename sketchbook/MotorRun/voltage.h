#include "Arduino.h"
#include "def.h"

unsigned long voltageMillis = millis();


void readVoltage(byte reading) {
  char floatStrCalc[10]= {'aaaaaaaa'};
  char floatStrBus[0];
  char StrBuff[15] = {'Hello'};
  int pin = 0; // 0 = Electroinics Voltage
  String name = "None";   //name of pin being addressed

  switch (reading) {
    case  ELECTRONICS :
      strcpy(StrBuff,"Electronic ");
      name = "Electronic ";
 //     StrBuff[] = "Electronic ";
      break;
    case  MOTORS :
    strcpy(StrBuff,"Motor ");
      name = "Motor ";
  //    StrBuff[] = "Motor ";
      break;
    case  PROCESSOR :
  strcpy(StrBuff,"Processor ");
      name = "Processor ";
   //   StrBuff[] = "Processor ";
      break;
    default :
      name = "Unknown ";
      break;
  }



  int busCounts = analogRead(reading);
 //   Serial.print("VoltageCount=");
 //    Serial.println(busCounts);
  float calcVoltage = busCounts / 41.322; // 24.75 / 1023 = .0242 = 1/41.322

  dtostrf(calcVoltage, 4, 2, floatStrCalc);

//  Serial.print (reading);
  Serial.print (StrBuff);
//  Serial.print (floatStrCalc);
//  Serial.println(" Voltage=" + floatStrCalc + " V");
  Serial.print("Voltage=");
  Serial.print(floatStrCalc);
    Serial.println("V");

}

void voltageCheck(unsigned long currentMillis){
  
  // Check voltage evry (50 * 250 s) or ~12.5 seconds
//  millis() - voltageMillis > 1000
  if ((currentMillis - voltageMillis) >5000) {
    //Serial.println("Voltage= 5000 loop");
    
    voltageMillis = millis();    //millis();
    readVoltage(ELECTRONICS);  // 0 is pin 0 for the Electronics - 1 will be for motors
    }
//    else {
//    voltageMillis++;
//    
//    }
}
