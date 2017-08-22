// Sonar Sensor program for FFL Dewey Robot
// Author Ken Samuelson 
//  Date started 6/18/2017
// Last update by Ken Samuelson 8/19/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.






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

const int trigPin = 2;    //Trig - green Jumper
const int echoPin = 4;    //Echo - yellow Jumper
long duration, cm, inches;
long distance=0;

int wait_sonar = 250;  //set compass reading  wait  time
unsigned long sonarMillis = millis();

  long convertCM(long); 
  long convertIN(long);
  void printDistance(long);
 long getSonar(boolean);
 
 byte localSonarCounter =0;
long sonarArray[3];
long sonarAverage();
void addSonar(long sensor);
boolean noSonar = false;

boolean setupSonar()
{
  Serial.println("Sonar Setup Begin");
  boolean noSonar=true;
  //Define sonar inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  long thisDuration = getSonar(false);
  Serial.print("thisDuration:");
  Serial.println(thisDuration);
  
  if (thisDuration == 0)
  {
    noSonar = true;
    Serial.println("No Sonar found or not working");
    }
    else 
    {
    noSonar = false;
    Serial.println("Sonar found and working");
        }
        
     Serial.println("Sonar Setup complete");
    return noSonar;
  }
  
  long convertCM(long duration)
  {
      cm = (duration / 2) / 29.1;
  return cm;
}

 long convertIN(long duration)
  {
  inches = (duration / 2) / 74;
  return inches;
}


long sonarAverage(){

          
          float localSonarAvg = (sonarArray[0]+sonarArray[1]+sonarArray[2])/3;
          Serial.print(" local Sonar Average: ");
          Serial.println(localSonarAvg);
 
  
  return localSonarAvg;
}

void addSonar(long sensor){
 // Display avererage everytime one is added.  This can be lots if turend on. 
  // float localAVG = headingAverage();
//  if (headingDiff(localAVG, heading)< 30){
  sonarArray[localSonarCounter] = sensor;
          if (localSonarCounter<2)
            localSonarCounter++;
          else
            localSonarCounter=0;
//}
//else {
//Serial.print("Bad heading reading ");
//Serial.print(heading);
//Serial.print(", Average reading");
//Serial.println(localAVG);

//}


}

long getSonar(boolean noSonar1) {
  duration = 0;
  if (!noSonar1){
  // The sonar is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sonar: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH); // without timeout
  //  with timeout but doesn't seem to workwell
 // duration = pulseIn(echoPin, HIGH,2000);
  
    if (duration == 0) {
    Serial.print("Duration=");
    Serial.println(duration);
    //printDistance(duration);
    Serial.print(" Dewey Stopped because of Sonar 0 ");
  }
  }
  return duration;
}

void printDistance(long duration) {
  cm = convertCM(duration);
  inches = convertIN(duration);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm  ");
}

long sonarTime(boolean noSonar1, unsigned long nowMillis4){
    // Do not EVER Put anything here - The gets run 1000 tiems a second.
     // check mills and do this every 60 ms  using wait_compass above.
     
    if (((nowMillis4 - sonarMillis) >= wait_sonar) && !noSonar) {
          sonarMillis = nowMillis4;
      distance = getSonar(noSonar1);
      return distance;
      }
    } 

long getDistance(){
 
      return distance;
  
}
