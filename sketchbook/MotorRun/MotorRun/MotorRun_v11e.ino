// Motor Run with pins 5,6,   10,11

#include "Arduino.h"
#include "Drive.h"
#include "voltage.h"
#include "def.h"

const int oneSecInUsec = 1000000; // a second in micro second units

/*
 * created by Rui Santos, http://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11 now 2
        Echo: Echo (OUTPUT) - Pin 12 now 4
        GND: GND
 */
 
const int trigPin = 2;    //Trig - green Jumper
const int echoPin = 4;    //Echo - yellow Jumper
long duration, cm, inches;

  char readVal= '$';
  byte bytVal = 74;
  char buffer[20];

  char buffer1[20];
  byte counter =0;

  String message1 = "Hello Pi from Arduino";
  String message2 = "counter=";
  String message3 = "Pi recevied=";
 // String message4 = "Interpret as a =";
 // String drivespeedMessage= "DriveSpeed =";
 // String drivestatusMessage = "DeweyMoving =";


  char oldSpeed = '$';
  char currentSpeed = '7';
  char oldMove = 'd';
  char currentMove = 'S';

 byte oldSensorSpeed;
boolean flagSensorGo = false;
boolean flagSensorStop = false;

 Drive dewey;
 byte voltCount=0;
 

void setup()
{

  
  Serial.begin(115200);

  Serial.println("Dewey Alive and ready to take commands");
  
// Looks Like these lines are irrelevant and don't remain in scope for the full program.   
//   Drive dewey;


  //Serial.println(drivespeedMessage + dewey.readSpeed());
  
  //dewey.checkValue('2');

  //Serial.println(drivespeedMessage + dewey.readSpeed());
  
    //Define sensor inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

void loop()
{
 

    
  if (Serial.available())
  {
     readVal = Serial.read();
     //Serial.print("Command Received=");
     //Serial.println(readVal);
     
     dewey.checkValue(readVal);
     
     // setup th eprint buffer
     //sprintf(buffer,'Pi recevied= %c',readVal);
     // Print the Print buffer 
     //Serial.println(buffer);
     // print second buffer
   //  Serial.println(message3 + readVal);

     //(Serial.read() - '0')
     // dewey.runSpeed((16 * intVal)-1);

     
  }
  

// run the update sequnece. May not be needed since the checkValue Updates
 // dewey.driveUpdate();
  
 delay(250);
  
  // send drive status to Pi
  // dewey.driveStatus();
 
  
  // Serial.println('Hello Pi from Arduino, I am alive');
     
//    Serial.println(message1);
//     Serial.println(message2 + counter);
//     counter= counter+1;
  
  // don't print if same as last time -Print once only
 currentSpeed = dewey.readSpeed();
  if (currentSpeed != oldSpeed){

     Serial.print("  OldSpeed=");
     Serial.print(oldSpeed);
    // Serial.println(drivespeedMessage + currentSpeed);
     Serial.print(" NewSpeed=");
     Serial.println(currentSpeed);
     
    oldSpeed = currentSpeed;

  }
  
     // don't print if same as last time
     currentMove = dewey.driveStatus();
   if (currentMove != oldMove){
     
     //Serial.println(drivestatusMessage + dewey.driveStatus());
//     Serial.print("NewMove once"+oldMove);
     Serial.print("  OldMove=");
     Serial.print(oldMove);
     Serial.print(" NewMove=");
     Serial.println(currentMove);

     oldMove = currentMove;

   }
   
   if (voltCount > 12) {
   // Read and print the voltage f
  readVoltage(ELECTRONICS);  // 0 is pin 0 for the Electronics - 1 will be for motors
    //  See def.h enum parameter
  // print disstance too
    printDistance(duration);
    Serial.println(" interim");
    
    voltCount =0;
   }
   else
   {
     voltCount = voltCount +1;
   }
  
  duration =  getSensor();
      // convert the time into a distance
       cm = (duration/2) / 29.1;
      inches = (duration/2) / 74;   
   
        

  if (duration == 0) {
 
       Serial.print("Duration=");
        Serial.println(duration);
        printDistance(duration);
        Serial.print(" Dewey Stopped because of Sensor 0 ");
    
  }

        
        if (cm < 15 && duration >0){  // about 6 inches


    //      Serial.print(oldSensorSpeed );
  //        printDistance(duration);
  //        Serial.println("..Stopped");
          
 ///         if (flagSensorStop){
          // Only hold once 
//          Serial.print("Stopping...Drive Status pre ");
//         Serial.print(dewey.driveStatus() );
          dewey.driveHold();
//          Serial.print("Stopping...Drive Status post ");
//          Serial.println(dewey.driveStatus() );

 //         flagSensorGo = true;  
//          flagSensorStop = false; 
        }
    //    }else if (cm >15 and cm <20){
          
          
    //      dewey.runSpeed(128);
    //      Serial.print(oldSensorSpeed );
    //      Serial.println(" Slowing");
    //      flagSensorGo = true;  
    //      flagSensorStop = true;  
     //   } 
        else {
       
       
          
  //        if (flagSensorGo){
            dewey.driveResume();
            
    //    printDistance(duration);
    //    Serial.print(" resume Status ");
    //        Serial.print(oldSensorSpeed );
    //        Serial.println(" oldSpeed..");
    //        oldSensorSpeed = (((dewey.readSpeed() +1)/16) + byte('0') - 7);
     //     Serial.print(char(dewey.driveStatus() ));
     //     Serial.println(" interim or Resume...");
     //     flagSensorGo = false;
     //     flagSensorStop = true;  
     //        }
            
          
    //      dewey.runSpeed(oldSensorSpeed );
     
           
        }
        
        
        
          
 // }
       
   
}

long getSensor(){ 
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

void printDistance(long duration){
  
        cm = (duration/2) / 29.1;
        inches = (duration/2) / 74; 
  
        Serial.print(inches);
        Serial.print("in, ");
        Serial.print(cm);
        Serial.print("cm  ");
  
  
}
