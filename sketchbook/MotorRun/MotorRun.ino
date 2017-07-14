// Motor Run with pins 5,6,   10,11

#include "Arduino.h"
#include "Drive.h"
#include "voltage.h"
#include "def.h"
#include "sonar.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

#include "compass.h"


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
unsigned long currentMillis = millis();


byte oldSensorSpeed;
boolean flagSensorGo = false;
boolean flagSensorStop = false;

boolean compassEnabled = true;
float heading = 0;

Drive dewey;
byte voltCount = 0;
float headingArray[3];
byte headingCounter =0;



void setup()
{
  delay (2000);
  Serial.begin(115200);
  Serial.println("Dewey Alive and ready to take commands");
  //Edit this line wheen a significant chnag eis made so that the user knows
 //  what version fo Motor Run theyy are using 
  Serial.println("Dewey Drive Code Version 12");

setupSonar();  

  
  compassEnabled = compassInit();
  if (compassEnabled)
    {
    Serial.println("Magnetometer Test -X -Z"); Serial.println("");
    
  } else {
      /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
      }
      
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
}

void loop()
{
  
  currentMillis = millis();
  
  if (Serial.available())
  {
    readVal = Serial.read();
    dewey.checkValue(readVal);
  }
  // delay(250);
  
  if (currentMillis -previousMillis >= 250){
    previousMillis = currentMillis;
    // when compass available print 
  if (compassEnabled){
      heading = compass();
      headingArray[headingCounter] = heading;
      
        //Serial.print("   Compass Heading: ");
        //Serial.println(heading);

        
        if (headingCounter<2)
        headingCounter++;
        else
        headingCounter=0;
        float headingAvg = (headingArray[0]+headingArray[1]+headingArray[2])/3;
        Serial.print("   average: ");
        Serial.println(headingAvg);
        getAccel();
        }
    
    // for debug
//    Serial.print("  PreviousMillis=");
//    Serial.print(previousMillis);
//    Serial.print(" currentMillis=");
//    Serial.println(currentMillis);

  currentSpeed = dewey.readSpeed();
  if (currentSpeed != oldSpeed) {

    Serial.print("  OldSpeed=");
    Serial.print(oldSpeed);
    Serial.print(" NewSpeed=");
    Serial.println(currentSpeed);

    oldSpeed = currentSpeed;
  }

  currentMove = dewey.driveStatus();
  if (currentMove != oldMove) {

    Serial.print("  OldMove=");
    Serial.print(oldMove);
    Serial.print(" NewMove=");
    Serial.println(currentMove);

    oldMove = currentMove;
  }

  if (voltCount > 12) {
    readVoltage(ELECTRONICS);  // 0 is pin 0 for the Electronics - 1 will be for motors

    printDistance(duration);
    Serial.println(" interim");

    voltCount = 0;
  }
  else
  {
    voltCount = voltCount + 1;
  }

  duration =  getSensor();
  cm = convertCM(duration);
  inches = convertIN(duration);

  if (autonomous)
  {
    dewey.driveAutonomous(cm);
  }


  if (!autonomous && cm < 15 && duration > 0) { // about 6 inches
    dewey.driveHold();
  }
  else {
    dewey.driveResume();
  }
  
  autonomous = dewey.isAutonomous();
  
  } // currentMills is greater than time
  
}



