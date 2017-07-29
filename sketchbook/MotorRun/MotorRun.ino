// Motor Run Program for FFL Dewey Robot
// author Ken Samuelson 
//  Date started 6/18/2016
// Last update by Ken Samuelson 7/22/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

#include "compass.h"

// Motor Run with pins 5,6,   10,11

#include "Arduino.h"
#include "Drive.h"
#include "voltage.h"
#include "def.h"
#include "sonar.h"



 //NeoPixel LED Digital Strip Cylon Eye v1.10 Created by EternalCore
 // Library in /usr/share/arduino/libraries so it needs to eb declared here 
 // not sure why this is necessary
#include "Adafruit_NeoPixel.h"
#include "cylon.h"






// #include "timer.h"  // thought this was needed for millis() but it seems to work anyway

const int oneSecInUsec = 1000000; // a second in micro second units

/*
   created by Rui Santos, http://randomnerdtutorials.com

   Complete Guide for Ultrasonic Sensor HC-SR04

    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11 now 2
        Echo: Echo (OUTPUT) - Pin 12 now 4
        GND: GND
*/


char readVal = '$';
byte bytVal = 74;
char buffer[20];

char buffer1[20];
byte counter = 0;

String message1 = "Hello Pi from Arduino";
String message2 = "counter=";
String message3 = "Pi recevied=";
boolean autonomous = false;

char oldSpeed = '$';
char currentSpeed = '7';
char oldMove = 'd';
char currentMove = 'S';

unsigned long previousMillis = millis();

byte oldSensorSpeed;
boolean flagSensorGo = false;
boolean flagSensorStop = false;

// Assume compass and Sonar are avaialble until proven otherwise
boolean compassEnabled = true;
boolean noCompass = false;
boolean noSonar = false;

float heading = 0;

Drive dewey;



void setup()
{
  delay (2000);  //leave a 2 seoncd delay before th eprogram starts.  used for program download time. 
  Serial.begin(115200);
  Serial.println("Dewey Alive and ready to take commands");
  //Edit this line wheen a significant chnag eis made so that the user knows
 //  what version fo Motor Run theyy are using 
  Serial.println("Dewey Drive Code Version 14");

noSonar = setupSonar();  

// setupCylon();
initializeLED();
clearLED();   // Initialize all pixels to 'off'
  
  compassEnabled = compassInit();
  if (compassEnabled)
    {
    Serial.println("Magnetometer Test -X -Z - Initialized"); Serial.println("");
      /* Display some basic information on this sensor */
  displayCompassDetails();
    
  } else {
      /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    noCompass = true;
      }
      
Serial.println("Sonar and Compass Check Complete.");
  
}

void loop()
{
  
 
  if (Serial.available())
  {
    readVal = Serial.read();
    dewey.checkValue(readVal);
  }
  // delay(250);
  
  // Every 500 milliseconds (1/2 second)check these things - and Print when necessary
  if (millis() -previousMillis >= 500){
    previousMillis = millis();
    // when compass available print 


//   update the drive every 500 ms
    dewey.driveUpdate();
    headingAverage();
// for debug
//    Serial.print("  PreviousMillis=");
//    Serial.print(previousMillis);
//    Serial.print(" currentMillis=");
//    Serial.println(currentMillis);


  }  // currentMills - previousMills is less than than time



  duration =  getSensor(noSonar);
  cm = convertCM(duration);
  inches = convertIN(duration);


  

  
 // Check to see if we are in Autonomous mode.
   autonomous = dewey.isAutonomous();
  
   if (autonomous)
  {
    dewey.driveAutonomous(cm);
  }
  
    if (!autonomous && cm < 20 && duration > 0) { // about 6 inches
    dewey.driveHold();
  }
  else {
    dewey.driveResume();
  }
  

    if (compassEnabled){
  // Check Compass using wait time in compass.h
      compassTime();

  // Check accel using wait time in compass.h
      accelTime();
      
      }
  
// Voltage check   
    voltageCheck();

// Run Cylon program 

    runCylon();    
  
  
  
}  // End of Loop



