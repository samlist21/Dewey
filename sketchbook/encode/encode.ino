// Seperate Arduino Interrupt driven Encoder Program for FFL Dewey Robot
// Author Ken Samuelson 
//  Date started 8/26/2017
// Last update by Ken Samuelson 9/14/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.

#include "Arduino.h"

#include "encodeInt.h"


void setup()
  {
    // Note: if you stop and start the serial connection to the Arduino then Setup will be re-run. 
  delay (2000);  //leave a 2 seoncd delay before the program starts.  Used for program download time. 
  Serial.begin(115200);//
  //Serial.flush();
  Serial.println("Encoder Alive and ready to take commands");
  //Edit this line when a significant chnage is made so that the user knows
 //  what version fo Motor Run theyy are using 
  Serial.println("Encoder Drive Code Version 14");
  
  // setup Encoder
  setupEncoder();
  
  }
  
void loop()

{
  
}

