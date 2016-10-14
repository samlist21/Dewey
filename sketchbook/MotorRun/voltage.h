#include "Arduino.h"
#include "def.h"


void readVoltage(byte reading){
char floatStrCalc[10];
char floatStrBus[10];
int pin = 0; // 0 = Electroinics Voltage 
String name = "None";   //name of pin being addressed


//if (reading == ELECTRONICS){  // should make this an emun for Electronics and Motors
//    pin = 0; //  if enum this is not necessary
//    name = "Electronic ";
//    } else {  // will need case or other construct for more pins. 
//      pin = 1;
//    name = "Motor ";
//    }
//
//  I like the case statment better. KS

    switch(reading){
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

float calcVoltage = busCounts /41.322;  // 24.75 / 1023 = .0242 = 1/41.322

dtostrf(calcVoltage, 4, 2, floatStrCalc);

// dtostrf(busCounts, 4, 2, floatStrBus);

Serial.print (name);
// Serial.print("Bus counts="+ String(busCounts) + " counts,  ");
Serial.println("Voltage="+ String(floatStrCalc) + " V");

}
