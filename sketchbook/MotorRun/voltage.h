// Voltage Reading program for FFL Dewey Robot
// Author Ken Samuelson 
//  Date started 6/18/2017
// Last update by Ken Samuelson 8/19/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.

#include "Arduino.h"
#include "def.h"

unsigned long voltageMillis = millis();
 // voltagePin voltRead = ELECTRONICS;  
  int voltRead = 0; 

void readVoltage(int reading) {
  char floatStrCalc[10]= {'aaaaaaaa'};
  char floatStrBus[10];
  char StrBuff[15] = {'Hello'};
  
  

  float voltFactor =1;
  int pin = 0; // 0 = Electroinics Voltage
  String name = "None";   //name of pin being addressed

  switch (reading) {
    case  0 :
      strcpy(StrBuff,"Elect ");
      name = "Elec ";
      voltFactor = 41.322; // 24.75 / 1023 = .0242 = 1/41.322
 //     StrBuff[] = "Electronic ";
      break;
    case  1 :
       strcpy(StrBuff,"Motor ");
      name = "Motor ";
      voltFactor = 41.62; // 24.75 / 1023 = .0242 = 1/41.322
  //    StrBuff[] = "Motor ";
      break;
    case  2 :
      strcpy(StrBuff,"Proc  ");
      name = "Proc  ";
      voltFactor =104.9; // 5.04
   //   StrBuff[] = "Processor ";
      break;
    default :
      name = "Unknown ";
      break;
  }



  int busCounts = analogRead(reading);
//    Serial.print("VoltageCount=");
//    Serial.println(busCounts);
  float calcVoltage = busCounts / voltFactor;

  dtostrf(calcVoltage, 4, 2, floatStrCalc);

//  Serial.print (reading);
  Serial.print (StrBuff);
//  Serial.print (floatStrCalc);
//  Serial.println(" Voltage=" + floatStrCalc + " V");
  Serial.print("Voltage=");
  Serial.print(floatStrCalc);
    Serial.println("V");

}

void voltageCheck(unsigned long currentMillis2){
  
  // Check voltage evry (50 * 250 s) or ~12.5 seconds
//  millis() - voltageMillis > 1000
  if ((currentMillis2 - voltageMillis) > 15000) {
    //Serial.println("Voltage= 5000 loop");
    
    voltageMillis = currentMillis2;    //millis();
//      Serial.print("VoltageA1");
    readVoltage(voltRead);  // 0 is pin 0 for the Electronics - 1 will be for motors
    voltRead = voltRead +1;
    if (voltRead > 2)
       voltRead = 0;
    }
//    else {
//    voltageMillis++;
//    
//    }
}
