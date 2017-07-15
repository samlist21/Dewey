// Motor Run with pins 5,6,   10,11

#include "Arduino.h"
#include "Drive.h"
#include "voltage.h"
#include "def.h"
#include "sonar.h"
// #include "cylon.h"


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

 //NeoPixel LED Digital Strip Cylon Eye v1.10 Created by EternalCore
#include "Adafruit_NeoPixel.h"

//Settings:
#define PIN 5 //The Pin out your Neopixel DIN strip/stick is connected to (Default is 6)
#define TPIXEL 12 //The total amount of pixel's/led's in your connected strip/stick (Default is 60)
int wait_T=40; //This is the delay between moving back and forth and per pixel
int PixelCount=12; //Set this to the AMOUNT of Led's/Pixels you have or want to use on your strip And It can be used to tell where to Stop then return the eye at in the strip
int Pixel_Start_End=0; //Set this to where you want it to Start/End at
boolean UsingBar = false; //Set this to true If you are using the 8x1 Neopixel Bar Or you want to only use 3 leds for the scanner. 

byte cylonLED = false;
byte up = true;



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
unsigned long cylonMillis = millis();


byte oldSensorSpeed;
boolean flagSensorGo = false;
boolean flagSensorStop = false;

boolean compassEnabled = true;
float heading = 0;

Drive dewey;
byte voltCount = 0;
float headingArray[3];
byte headingCounter =0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(TPIXEL, PIN, NEO_GRB + NEO_KHZ800); //Standered Strip function




void setup()
{
  delay (2000);
  Serial.begin(115200);
  Serial.println("Dewey Alive and ready to take commands");
  //Edit this line wheen a significant chnag eis made so that the user knows
 //  what version fo Motor Run theyy are using 
  Serial.println("Dewey Drive Code Version 12");

setupSonar();  

// setupCylon();
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
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
    
      if (currentMillis - cylonMillis >= wait_T) {
    // save the last time you blinked the LED
    cylonMillis = currentMillis;

    if (up) {
  //Example: CylonEyeUp(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait_T, PixelCount, Pixel_Start_End);
  CylonEyeUp(strip.Color(175,0,0), strip.Color(25,0,0), strip.Color(10,0,0), wait_T, PixelCount, Pixel_Start_End);
    
    }
  else{
  //Example: CylonEyeDown(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait_T, PixelCount, Pixel_Start_End);
  CylonEyeDown(strip.Color(0,0,175), strip.Color(0,0,25), strip.Color(0,0,10), wait_T, PixelCount, Pixel_Start_End);
  
  
  }
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


void CylonEyeUp(uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pStart) {
  static int i = pStart;
  //for(int i=pStart; i<TotalPixels; i++) {
  if (i<TotalPixels){
    strip.setPixelColor(i+2, Ctt);  //Third Dot Color
    strip.setPixelColor(i+1, Ct);   //Second Dot Color
    strip.setPixelColor(i, Co);     //Center Dot Color
    strip.setPixelColor(i-1, Ct);   //Second Dot Color
    
    strip.setPixelColor(i-2, Ctt);  //Third Dot Color

    strip.setPixelColor(i-3, strip.Color(0,0,0)); //Clears the dots after the 3rd color

    strip.show();
    i++;}
    else {
    i = pStart;
    up = false;
    }
    
    //Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);
  
}
void CylonEyeDown(uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pEnd) {
  static int i = TotalPixels-1;
  
  //for(int i=TotalPixels-1; i>pEnd; i--) {
  if (i>pEnd){
    strip.setPixelColor(i-2, Ctt);  //Third Dot Color
    strip.setPixelColor(i-1, Ct);   //Second Dot Color
    strip.setPixelColor(i, Co);    //Center Dot Color
    strip.setPixelColor(i+1, Ct);  //Second Dot Color
    
    strip.setPixelColor(i+2, Ctt);  //Third Dot Color

     strip.setPixelColor(i+3, strip.Color(0,0,0)); //Clears the dots after the 3rd color

    strip.show();
//    Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);
  i--;
  }
  else{
    i= TotalPixels-1;
    up = true;
  }
}

void clearCylon(int TotalPixels, int pEnd) {
  for(int i=TotalPixels-1; i>pEnd; i--) {
      strip.setPixelColor(i, strip.Color(0,0,0)); //Clears the dots 
  //  strip.show();
//    Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);
  }
  strip.show(); //Now clear the bar
}



