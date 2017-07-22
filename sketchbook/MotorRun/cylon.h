
 //NeoPixel LED Digital Strip Cylon Eye v1.10 Created by EternalCore
// #include "Adafruit_NeoPixel.h"
// #include "cylon.h"
//#include <Adafruit_NeoPixel.h>

// Needs to be called by MotorRun to find the file
//#include <"libraries/Adafruit_NeoPixel.h">

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(TPIXEL, PIN, NEO_GRB + NEO_KHZ800); //Standered Strip function


void clearCylon(Adafruit_NeoPixel strip1, int TotalPixels, int pEnd) {
  for(int i=TotalPixels-1; i>pEnd; i--) {
      strip1.setPixelColor(i, strip1.Color(0,0,0)); //Clears the dots 
  //  strip.show();
//    Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);
  }
  strip1.show(); //Now clear the bar
}

boolean CylonEyeUp(Adafruit_NeoPixel strip1, uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pStart) {
  static int i = pStart;
  static boolean up =true;
  //for(int i=pStart; i<TotalPixels; i++) {
  if (i<TotalPixels){
    strip1.setPixelColor(i+2, Ctt);  //Third Dot Color
    strip1.setPixelColor(i+1, Ct);   //Second Dot Color
    strip1.setPixelColor(i, Co);     //Center Dot Color
    strip1.setPixelColor(i-1, Ct);   //Second Dot Color
    
    strip1.setPixelColor(i-2, Ctt);  //Third Dot Color

    strip1.setPixelColor(i-3, strip1.Color(0,0,0)); //Clears the dots after the 3rd color

    strip1.show();
    i++;}
    else {
    i = pStart;
    up = false;
    }
    
    //Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);
  return up;
  
}


boolean CylonEyeDown(Adafruit_NeoPixel strip1, uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pEnd) {
  static int i = TotalPixels-1;
  static boolean up = false;
  
  //for(int i=TotalPixels-1; i>pEnd; i--) {
  if (i>pEnd){
    strip1.setPixelColor(i-2, Ctt);  //Third Dot Color
    strip1.setPixelColor(i-1, Ct);   //Second Dot Color
    strip1.setPixelColor(i, Co);    //Center Dot Color
    strip1.setPixelColor(i+1, Ct);  //Second Dot Color
    
    strip1.setPixelColor(i+2, Ctt);  //Third Dot Color

     strip1.setPixelColor(i+3, strip1.Color(0,0,0)); //Clears the dots after the 3rd color

    strip1.show();
//    Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);
  i--;
  }
  else{
    i= TotalPixels-1;
    up = true;
  }
  
  return up;
  
}


class Cylon{
  
    
   public:
   void runCylonEye(void);
   void cylonSetup(void );
   
   private:

#define PIN 7 //The Pin out your Neopixel DIN strip/stick is connected to (Default is 6)
#define TPIXEL 29 //The total amount of pixel's/led's in your connected strip/stick (Default is 60)
int wait_T=60; //This is the delay between moving back and forth and per pixel
int PixelCount=29; //Set this to the AMOUNT of Led's/Pixels you have or want to use on your strip And It can be used to tell where to Stop then return the eye at in the strip
int Pixel_Start_End=0; //Set this to where you want it to Start/End at
boolean UsingBar = false; //Set this to true If you are using the 8x1 Neopixel Bar Or you want to only use 3 leds for the scanner. 

byte cylonLED = true;
byte up = true;
int pStart = 0;

  
  Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(TPIXEL, PIN, NEO_GRB + NEO_KHZ800); //Standered Strip function

  
  const uint32_t  Red = strip3.Color(175,0,0);
  const uint32_t  RedMed = strip3.Color(25,0,0);
  const uint32_t  RedFaint = strip3.Color(10,0,0);
  
  const uint32_t  Blue = strip3.Color(0,0,175);
  const uint32_t  BlueMed = strip3.Color(0,0,25);
  const uint32_t  BlueFaint = strip3.Color(0,0,10);

  

  


boolean CylonEyeUp1( uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pStart) {
  static int i = pStart;
  static boolean up =true;
  //for(int i=pStart; i<TotalPixels; i++) {
  if (i<TotalPixels){
    strip3.setPixelColor(i+2, Ctt);  //Third Dot Color
    strip3.setPixelColor(i+1, Ct);   //Second Dot Color
    strip3.setPixelColor(i, Co);     //Center Dot Color
    strip3.setPixelColor(i-1, Ct);   //Second Dot Color
    
    strip3.setPixelColor(i-2, Ctt);  //Third Dot Color

    strip3.setPixelColor(i-3, strip3.Color(0,0,0)); //Clears the dots after the 3rd color

    strip3.show();
    i++;}
    else {
    i = pStart;
    up = false;
    }
    
    //Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);

  return up;
}


boolean CylonEyeDown1( uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pEnd) {
  static int i = TotalPixels-1;
  //static boolean up = false;
  
  //for(int i=TotalPixels-1; i>pEnd; i--) {
  if (i>pEnd){
    strip3.setPixelColor(i-2, Ctt);  //Third Dot Color
    strip3.setPixelColor(i-1, Ct);   //Second Dot Color
    strip3.setPixelColor(i, Co);    //Center Dot Color
    strip3.setPixelColor(i+1, Ct);  //Second Dot Color
    
    strip3.setPixelColor(i+2, Ctt);  //Third Dot Color

     strip3.setPixelColor(i+3, strip3.Color(0,0,0)); //Clears the dots after the 3rd color

    strip3.show();
//    Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);
  i--;
  }
  else{
    i= TotalPixels-1;
    up = true;
  }
  
  return up;
  
}

  
  
boolean CylonEye(Adafruit_NeoPixel strip1, uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pStart) {
  static int i = pStart;
  //static boolean up =true;
  //for(int i=pStart; i<TotalPixels; i++) {
  if (i<TotalPixels){
    strip1.setPixelColor(i+2, Ctt);  //Third Dot Color
    strip1.setPixelColor(i+1, Ct);   //Second Dot Color
    strip1.setPixelColor(i, Co);     //Center Dot Color
    strip1.setPixelColor(i-1, Ct);   //Second Dot Color
    
    strip1.setPixelColor(i-2, Ctt);  //Third Dot Color

    strip1.setPixelColor(i-3, strip1.Color(0,0,0)); //Clears the dots after the 3rd color

    strip1.show();
    i++;}
    else {
    i = pStart;
    up = false;
    }
    
    //Serial.println(i); //Used For pixel Count Debugging
//    delay(Delay);
  return up;
  
}

};


 void Cylon::cylonSetup(void){ 
    strip3.begin();
    strip3.show(); // Initialize all pixels to 'off'
 }

void Cylon::runCylonEye (void){
    static boolean up =true;
       if (up) {
      //Example: CylonEyeUp(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait_T, PixelCount, Pixel_Start_End);
      up = CylonEyeUp1(Red, RedMed, RedFaint, wait_T, PixelCount, Pixel_Start_End);
        
        }
      else{
      //Example: CylonEyeDown(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait_T, PixelCount, Pixel_Start_End);
      up = CylonEyeDown1(Blue, BlueMed, BlueFaint, wait_T, PixelCount, Pixel_Start_End);
      
      
      }
}
