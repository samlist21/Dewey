// Motor Run Program for FFL Dewey Robot Arduino #2
// This is the second Arduino to manage heading board and 
// offload other operations. 
// author Ken Samuelson 
//  Date started 8/26/2017
// Last update by Ken Samuelson 8/26/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.

// Don't forget to change the device to /dev/ttyACM1

#include <Wire.h>  // Needed for compass to run
#include <Adafruit_Sensor.h> // Needed for compass to run
#include <Adafruit_LSM303_U.h> // Needed for compass to run

#include "Arduino.h"

#include "compass.h"

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




void setup()
  {
    // Note: if you stop and start the serial connection to the Arduino then Setup will be re-run. 
  delay (2000);  //leave a 2 seoncd delay before the program starts.  Used for program download time. 
  Serial.begin(115200);//
  //Serial.flush();
  Serial.println("Ard2 Alive and ready to take commands");
  //Edit this line when a significant chnage is made so that the user knows
 //  what version fo Motor Run theyy are using 
  Serial.println("Ard2 Drive Code Version 1");
  
  
  // setup Compass
  compassInit();

    Serial.println("Ard2 Setup Complete");
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
  Serial.print("Ard 2 ByteCount =");
  Serial.print(byteCount);      
    Serial.print(", Found Key=");
    Serial.print(readVal);
    Serial.print(" (char)");
    Serial.println(char(readVal));
    // dewey.checkValue(readVal);
 
    
  }
      
  
  }  // currentMills - previousMills is less than than time

// Read the current Compass Value 
  
  compassTime(nowMillis);
  
  
  // Read the current Acceleration Value 
  accelTime(nowMillis);
  
}  // End of Loop



