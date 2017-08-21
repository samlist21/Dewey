// Motor Run Program for FFL Dewey Robot
// author Ken Samuelson 
//  Date started 6/18/2016
// Last update by Ken Samuelson 7/22/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

 //NeoPixel LED Digital Strip Cylon Eye v1.10 Created by EternalCore
 // Library in /usr/share/arduino/libraries so it needs to eb declared here 
 // not sure why this is necessary
#include "Adafruit_NeoPixel.h"
#include "cylon.h"

//#include "compass.h"

// Motor Run with pins 5,6,   10,11

#include "encode.h"
#include "Arduino.h"
#include "Drive.h"
#include "voltage.h"
#include "def.h"
#include "sonar.h"



//char readVal = '$';
//byte bytVal = 74;
//char buffer[20];
//
//char buffer1[20];
//byte counter = 0;

int bytesAvailable=0;

unsigned long nowMillis = millis(); 
unsigned long previousMillis = nowMillis;

long readValCounter =0;

// Assume compass and Sonar are availble until proven otherwise
boolean compassEnabled = true;
boolean noCompass = false;


float heading = 0;
int byteCount = 0;
byte readVal = 32;


 Drive dewey;

void setup()
  {
    // Note: if you stop and start the serial connection to the Arduino then Setup will be re-run. 
  delay (2000);  //leave a 2 seoncd delay before the program starts.  Used for program download time. 
  Serial.begin(115200);//
  //Serial.flush();
  Serial.println("Dewey Alive and ready to take commands");
  //Edit this line when a significant chnage is made so that the user knows
 //  what version fo Motor Run theyy are using 
  Serial.println("Dewey Drive Code Version 14");
  
  // setup Encoder
  setupEncoder();
 
  // setup Cylon 
  cylonSetup(); 

 // Setup sonar  - if not connected or readign 0 then set to true
  noSonar = setupSonar();

    Serial.println("Dewey Setup Complete");
}

void loop()
{
  
 
  nowMillis = millis();


   
  // Every 500 milliseconds (1/2 second)check these things - and Print when necessary
  if ((nowMillis - previousMillis) > 250){

//      // Test to see if commend look is running
//        Serial.print("2PreviousMillis=");
//        Serial.print(previousMillis);
//        Serial.print(", nowMillis=");
//        Serial.print(nowMillis);
//        unsigned long diffMillis = nowMillis - previousMillis;
//        Serial.print(", Diff=");
//        Serial.println(diffMillis);

    previousMillis = millis();

      
    // when compass available print 
  //  Serial.println("  500 msecond timer");

  byteCount = Serial.available();
//  Serial.print("ByteCount =");
//  Serial.print(byteCount);
  if (byteCount >0) // = -1 if none avaialble if more than one start reading them. 4 per second.
  {
    readVal = Serial.read();
  Serial.print("ByteCount =");
  Serial.print(byteCount);      
    Serial.print(", Found Key=");
    Serial.print(readVal);
    Serial.print(" (char)");
    Serial.println(char(readVal));
    dewey.checkValue(readVal);
 
    
  }
      
  
  }  // currentMills - previousMills is less than than time

  // Check sonar distance
    sonarTime(noSonar, nowMillis);
    
  // Read encoder
  encoderTime(nowMillis);  

  // Run Cylon program 

    runCylon(nowMillis, cylonEnable);

  // Run Voltage Check 
    voltageCheck(nowMillis);

  
}  // End of Loop



