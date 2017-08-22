// Cylon NeoPixel LED strip program for FFL Dewey Robot
// Author Ken Samuelson 
//  Date started 6/18/2017
// Last update by Ken Samuelson 7/22/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.


 //NeoPixel LED Digital Strip Cylon Eye v1.10 Created by EternalCore
 // Attempted all these library linkages but none worked .  Only in motorRun.ino 
// #include "Adafruit_NeoPixel.h"
// #include "cylon.h"
//#include </usr/share/arduino/libraries/Adafruit_NeoPixel_master/Adafruit_NeoPixel.h>
//#include </usr/share/arduino/libraries/Adafruit_NeoPixel_master/Adafruit_NeoPixel.h>

//#include </usr/share/arduino/libraries/Adafruit_NeoPixel_master/Adafruit_NeoPixel.h>

// Needs to be called by MotorRun to find the file
//#include <"libraries/Adafruit_NeoPixel.h">

#define PIN 7 //The Pin out your Neopixel DIN strip/stick is connected to (Default is 6)
#define TPIXEL 29 //The total amount of pixel's/led's in your connected strip/stick (Default is 60)
int wait_T=100; //This is the delay between moving back and forth and per pixel

// Wait time is handled by motorRun Program not here but coudl be done here as well. 
int PixelCount=21; //Set this to the AMOUNT of Led's/Pixels you have or want to use on your strip And It can be used to tell where to Stop then return the eye at in the strip
int Pixel_Start_End=5; //Set this to where you want it to Start/End at

//Standard Strip function
Adafruit_NeoPixel strip = Adafruit_NeoPixel(TPIXEL, PIN, NEO_GRB + NEO_KHZ800); 

boolean cylonEnable = true; 
int cylonCounter=0;
boolean up =true;
unsigned long cylonMillis = millis();


void cylonSetup(){
    strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 
  
}


void initializeLED() {
   strip.begin();
   
}

void clearLED() {
 
  strip.clear(); //Now clear the bar
  strip.show();

}

void CylonEyeUp( uint32_t Co, uint32_t Ct, uint32_t Ctt) {
  static int pStart = Pixel_Start_End;  // this is the start point

//  clear LED strip before you start
  strip.clear();
  
    int i = pStart;
    if (pStart<PixelCount){
  //  Full the dot buffer
    
    strip.setPixelColor(i+2, Ctt);  //Third Dot Color
    strip.setPixelColor(i+1, Ct);   //Second Dot Color
    strip.setPixelColor(i, Co);     //Center Dot Color
    strip.setPixelColor(i-1, Ct);   //Second Dot Color
    strip.setPixelColor(i-2, Ctt);  //Third Dot Color
    
    strip.show();
   
    pStart++;
    }
  
   else {
    pStart = Pixel_Start_End;  //Reset to the start point.
    up = false;
    
    }
//    Serial.print(" U"); //Used For pixel Count Debugging
//    Serial.print(i); //Used For pixel Count Debugging
  
}

void CylonEyeDown( uint32_t Co, uint32_t Ct, uint32_t Ctt) {
  static int pEnd = PixelCount;
  int i = pEnd;
  
//  clear LED Strip before you start

  strip.clear();
 
  if (i>Pixel_Start_End){
    // strip1.setPixelColor(i-3, strip1.Color(0,0,0)); //Clears the first dot after the 3rd color
    strip.setPixelColor(i-2, Ctt);  //Third Dot Color
    strip.setPixelColor(i-1, Ct);   //Second Dot Color
    strip.setPixelColor(i, Co);    //Center Dot Color
    strip.setPixelColor(i+1, Ct);  //Second Dot Color
    
    strip.setPixelColor(i+2, Ctt);  //Third Dot Color

     strip.show();
//    Serial.print(" D"); //Used For pixel Count Debugging
//    Serial.print(i);  //Used For pixel Count Debugging

  pEnd--;
  }
  else{
    pEnd= PixelCount;
    up = true;
  
  }
 

}


void runCylon(unsigned long nowMillis7, boolean cylonEnable1){
  // Do not EVER Put anything here - The gets run 1000 tiems a second.
   // check mills and do this every 60 ms  using wait_T above.
    if (((nowMillis7 - cylonMillis) > wait_T) &&  cylonEnable1) {

    // save the last time you blinked the LED string
    cylonMillis = nowMillis7;
  
        if (up) {
    //cylon.runCylonEye();
    // Run Red
    CylonEyeUp(0x00AF0000, 0x00570000, 0x000A0000);
//      //OLD Example: CylonEyeUp(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait_T, PixelCount, Pixel_Start_End);
//      up = CylonEyeUp(strip, strip.Color(175,0,0), strip.Color(25,0,0), strip.Color(10,0,0), wait_T, PixelCount, Pixel_Start_End);

        
        }
      else{
        // Run Blue
//      //  OLD Example: CylonEyeDown(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait_T, PixelCount, Pixel_Start_End);
//      up = CylonEyeDown(strip, strip.Color(0,0,175), strip.Color(0,0,25), strip.Color(0,0,10), wait_T, PixelCount, Pixel_Start_End);
      CylonEyeDown(0x000000AF, 0x00000019, 0x0000000a);
      }
      
      
     // Test to see if cylon is running
     // For every 1000 changes in cylon value print out the status
     cylonCounter++;
     if (cylonCounter > 1000){
       Serial.println("Cylon working");
       cylonCounter =0;
     }
      
      
    } // cylon Mills met
}

