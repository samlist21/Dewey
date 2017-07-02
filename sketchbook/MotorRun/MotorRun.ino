// Motor Run with pins 5,6,   10,11

#include "Arduino.h"
#include "Drive.h"
#include "voltage.h"
#include "def.h"

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

byte oldSensorSpeed;
boolean flagSensorGo = false;
boolean flagSensorStop = false;

Drive dewey;
byte voltCount = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Dewey Alive and ready to take commands");
  //Edit this line wheen a significant chnag eis made so that the user knows
 //  what veersion fo Motor Run theyy are using 
  Serial.println("Dewey Drive Code Version 12");

  //Define sensor inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  if (Serial.available())
  {
    readVal = Serial.read();
    dewey.checkValue(readVal);
  }
  delay(250);

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
  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;

  if (autonomous)
  {
    dewey.driveAutonomous(cm);
  }

  if (duration == 0) {
    Serial.print("Duration=");
    Serial.println(duration);
    printDistance(duration);
    Serial.print(" Dewey Stopped because of Sensor 0 ");
  }
  if (!autonomous && cm < 15 && duration > 0) { // about 6 inches
    dewey.driveHold();
  }
  else {
    dewey.driveResume();
  }
}

long getSensor() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  return duration;
}

void printDistance(long duration) {
  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm  ");
}
