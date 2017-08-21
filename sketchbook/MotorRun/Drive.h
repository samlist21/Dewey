// Drive program for FFL Dewey Robot
// Author Ken Samuelson 
//  Date started 6/18/2017
// Last update by Ken Samuelson 8/19/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.


//#include "compass.h"
//#include "math.h"


class Drive {
    const int Left_CW = 5;
    const int Left_CCW = 6;

    const int Right_CCW = 10;
    const int Right_CW = 11;

    const int ledPin = 13;
    const int rightCompDefault = 4;
    const int leftCompDefault = 0;
    
    byte Right_Comp = 4;
    byte Left_Comp = 0;
    const byte RightBack_Comp = 0;
    const byte LeftBack_Comp = 15;
    

    byte holdCommand;
    byte slowSpeed;
    long prevCm;
    int driveRight = 0;
    boolean autonomous = false;
    


  public:
    Drive();
    void driveAutonomous(long);
    byte isAutonomous();
    void driveUpdate();
    byte driveStatus();
    void runSpeed(byte );
    byte readSpeed();
    void driveSTOP();
    void driveFWD();
    void driveHold();
    void driveSlow();
    void driveResume();
    void checkValue (byte);
    void headingCompensate();
    void driveDisplayHeading();
    void driveCompReset();
    void rightCompUp();
    void rightCompDown();

  private:
    byte driveSpeed = 100 ;
    boolean hold = false;
    boolean slow = false;
    float setHeading = 0;
    float driveHeading = 0;
    float difference = 0;
    
    byte driveDirection = 'S';  // Start in STOP mode
    byte driveCommand = 'S';  // Start drive command STOP
    
    void driveBACK();
    void driveRIGHT();
    void driveLEFT();
};

Drive::Drive () {
  driveSpeed = 128;
  pinMode(Left_CW, OUTPUT);
  pinMode(Left_CCW, OUTPUT);
  pinMode(Right_CCW, OUTPUT);
  pinMode(Right_CW, OUTPUT);
};


void Drive::driveHold () {
  if (hold != true) {
    holdCommand = driveDirection;
    driveDirection = 'S';  // set to stop
    // could be set to backwards
    checkValue(driveDirection);
    hold = true;
    Serial.println("Hold mode ON");
  }
};

void Drive::driveSlow () {
  if (slow != true) {
    slowSpeed = driveSpeed;
    driveSpeed = 144;  // set to = to "1"
    slow = true;
  }
};

void Drive::driveResume () {
  if (hold == true) { // run this case only once after a hold
    hold = false;
    slow = false;
    driveDirection = holdCommand;
    checkValue(driveDirection);
    Serial.println("Hold mode OFF =====");
  };
};

void Drive::runSpeed (byte amount) {
  driveSpeed = amount;
};

byte Drive::readSpeed () {
  int driveSpeed1 = int(driveSpeed);
  byte outSpeed = (((driveSpeed1 + 1) / 16) + byte('0') - 7);
  return byte(outSpeed);
};


void Drive::driveAutonomous (long cm)
{
  if (autonomous)
  {
    if (cm <= 20)
    {
      if (cm < prevCm)
      {
        driveRight = false;
      }
      if (driveRight)
      {
        driveDirection = 'R';
      }
      else
      {
        driveDirection = 'L';
      }
    }
    else
    {
      driveRight = 0;
      driveDirection = 'F';
    }
    prevCm = cm;
  }
};


// this is the drive action that updates any changed parameters on the drive
void Drive::driveUpdate () {
  

  
  if (driveDirection == 'F' ) {
    
  //      if (hold != true) {
          // Hold - Don't go forward if in hold
  // read compass
    
   // headingCompensate();
    driveFWD();
    
    // driveDisplayHeading();
    // use the above instead of the below.
    
 //   driveHeading = headingAverage();

 //   difference = (( driveHeading - setHeading +180) % (float) 360) -180;
//    difference = headingDiff(setHeading,driveHeading);
//    Serial.print("Update setHeading=");
//    Serial.print(driveHeading);
//    Serial.print(", AVG driveHeading=");
//    Serial.print(driveHeading);
//    Serial.print("  Heading Diff=");
//    Serial.println(difference);
    
 //     } // End hold
  }  // End Forward
  if (driveDirection == 'B' ) {
    driveBACK();
  }
//  
//    if (autonomous &  hold) {
//     Serial.println(" Autonomous Right");
//    driveRIGHT();
//        }
//    
//    if (autonomous &  ~hold){
//      Serial.println(" Autonomous FWD");
//    driveFWD();
//    
//         }


  if (driveDirection == 'S' ) {
    
    driveSTOP();
  }
  
  if (driveDirection == 'N' ) {
      // Done turning 90 degreesleft - Possibly 88 should be changable if the speed is changed on the turn.

//  float compass1 = compass();
//  float difference = headingDiff(setHeading, compass());
//          Serial.print(" Compass : ");
//          Serial.print(compass1);
//          Serial.print(" Set Heading : ");
//          Serial.print(setHeading);
//          Serial.print(" Turn Difference: ");
//          Serial.println(difference);
  //readEncoder();
//  int a = encoderDiff();
//   Serial.print(" Encoder Diff: ");
//    Serial.println(a); 
//  
//      if (encoderDiff()< -30 || encoderDiff()> 30 ){
////      if (headingDiff(setHeading, compass())< -89){
//      driveDirection = 'F';
//    driveFWD();
//    Serial.print(" Heading Diff: ");
//    Serial.print(headingDiff(setHeading, compass())); 
//    Serial.print(" Encoder Diff: ");
//    Serial.println(a); 
//    Serial.println("--Left Turn 90 degrees complete");
//      }
  }
  
      if (driveDirection == 'M' ) {
//          float compass1 = compass();
//  float difference = headingDiff(setHeading, compass());
//          Serial.print(" Compass : ");
//          Serial.print(compass1);
//          Serial.print(" Set Heading : ");
//          Serial.print(setHeading);
//          Serial.print(" Turn Difference: ");
//          Serial.println(difference);
        
        // Done turning 90 degrees rightt 
//              if (encoderDiff()> 30 || encoderDiff()< -30){
////      if (headingDiff(setHeading, compass()) > 89){
//      driveDirection = 'F';
//    driveFWD();
//    Serial.print(" Heading Diff: ");
//    Serial.print(headingDiff(setHeading, compass()));  
//    Serial.println("Right Turn 90 degrees complete");
//      }
  }
  
  
  // check if in autonomous mode

};


void Drive::driveDisplayHeading(){
      
    Serial.print("Status Start Heading=");
    Serial.print(setHeading);   
    Serial.print(", driveHeading=");
    Serial.print(driveHeading);
    Serial.print(",  Heading Diff=");
    Serial.print(difference);
    Serial.print(",  RightComp=");
    Serial.println(Right_Comp);
  };

void Drive::headingCompensate(){
      // use average heading value for difference calculation
   //   driveHeading = headingAverage();
   // use immediate heading value for difference calculation
    //  driveHeading = compass();
   // readEncoder();

 //      Calculate the heading difference   
   //  difference = headingDiff(setHeading,driveHeading);
//    int encoderDiff1 = encoderDiff();
//// Compensate for the difference in heading
//     //if (difference > 3){
//     if (encoderDiff1 > 2) {
//     void rightCompUp();
//     //driveDisplayHeading();
//    }
//    // else if (difference < -3){
//    else if (encoderDiff1 < -2) {
//    rightCompDown();;
//    //driveDisplayHeading();
//    }
//    else
    driveCompReset();
  };

byte Drive::driveStatus () {

   //readEncoder();
   //headingCompensate();
    // Turn on to display the heading and comp
  //  driveDisplayHeading();

    driveUpdate();
    
  
  return driveDirection;
};


// this is the command processor that handles changes in commands
void Drive::checkValue (byte value) {


    if (value >= '0' and value <= '9') {
      byte oldSpeed = driveSpeed;
      driveSpeed = ((((value - '0') + 6) * 16) + 15);
      
// Print Change for debugging
    Serial.print("OldSpeed=");
    Serial.print( String(oldSpeed,DEC));
    Serial.print(", NewSpeed(char) value=");
    Serial.print((char) value);   
    Serial.print(", NewSpeed(dec) value=");
    Serial.println( String(driveSpeed,DEC));
  
      
    }
    else {
//      setHeading = compass();
      encoderClear();
           
      byte oldMove = driveDirection;
      
    switch (value) {
      case 'x':
      case 'X':
        driveDirection = 'S';
        driveSTOP();
        break;
      case 's':
      case 'S':
      case '0':
        driveDirection = 'S';
        if (autonomous)
        {
          autonomous = false;
          Serial.println("Autonomous mode OFF");
        }
        driveSTOP();
        break;
      case 'f':
      case 'F':
        driveDirection = 'F';
//    setHeading = headingAverage();
//    displayHeading();

// Reset Compensation values to default
    driveCompReset();


// Store heading value  before we start moving  - test both

//     // Store average heading so we can compare with while traveling
     //setHeading = headingAverage();
     // Store current heading so we can compare with while traveling
//     setHeading = compass();

        driveFWD();
 // Store heading value  before we start moving - Test both
        
//     // Store average heading so we can compare with while traveling
     //setHeading = headingAverage();
     // Store current heading so we can compare with while traveling
   //  setHeading = compass();
     
    Serial.print("FWD - Heading ");
   // displayHeading(); 
        
        break;

      case 'c':
      case 'C':
       Serial.print(cylonEnable);
      // ToggleCylon
        cylonEnable = !cylonEnable;
         Serial.print("Toggling Cylon Enable ");
          Serial.println(cylonEnable);
          clearLED();
        
        break;

      case 'b':
      case 'B':
        driveDirection = 'B';
        driveBACK();
        break;

      case 'm':
      case 'M':
        driveDirection = 'M';
        // setHeading = compass();
        driveRIGHT();
        Serial.println("Turning Right 90 degrees");
        break;
      case 'r':
      case 'R':
        driveDirection = 'R';
        driveRIGHT();
        break;
      case 'n':
      case 'N':  // Turn left 90 degrees
        driveDirection = 'N';
        //setHeading = compass();
        driveLEFT();
        Serial.println("Turning Left 90 degrees");
        break;
      case 'l':
      case 'L':
        driveDirection = 'L';
        driveLEFT();
        break;
      case 'a':
      case 'A':
        if (autonomous){
          autonomous = false;
          Serial.println("Autonomous mode OFF");
        }
        else {
        autonomous = true;
       // driveAutonomous(20);
        Serial.println("Autonomous mode ON");
          }
        
        break;
      default:
      Serial.print("Error unknown Key (char)=");
      Serial.print(value);
      Serial.print(", value=");
      Serial.print(value,DEC);
      Serial.print(", 0x");
      Serial.print(value,HEX);
      Serial.println(", Hit Default step");
        break;
        
        }  //  End Switch       


// Print Change for debugging
    Serial.print("OldMove=");
    Serial.print((char) oldMove);
    Serial.print(", NewMove=");
    Serial.println((char) driveDirection);

    
        
    } // end else
    driveUpdate();

    
};


void Drive::driveFWD () {
  analogWrite(Left_CW, 0);
  analogWrite(Left_CCW, driveSpeed - Left_Comp);
  analogWrite(Right_CCW, 0);
  analogWrite(Right_CW, driveSpeed - Right_Comp);
  driveDirection = 'F';
};

void Drive::driveBACK () {
  analogWrite(Left_CW, driveSpeed - LeftBack_Comp);
  analogWrite(Left_CCW, 0);
  analogWrite(Right_CCW, driveSpeed - RightBack_Comp);
  analogWrite(Right_CW, 0);
  driveDirection = 'B';
};

void Drive::driveSTOP () {
  analogWrite(Left_CW, 0);
  analogWrite(Left_CCW, 0);
  analogWrite(Right_CCW, 0);
  analogWrite(Right_CW, 0);
  driveDirection = 'S';
};

void Drive::driveRIGHT () {
  analogWrite(Left_CW, 0);
  analogWrite(Left_CCW, driveSpeed / 2);
  analogWrite(Right_CCW, driveSpeed / 2);
  analogWrite(Right_CW, 0);
  
  if (driveDirection != 'M')
  driveDirection = 'R';
};

void Drive::driveLEFT () {
  analogWrite(Left_CW, driveSpeed / 2);
  analogWrite(Left_CCW, 0);
  analogWrite(Right_CCW, 0);
  analogWrite(Right_CW, driveSpeed / 2);
  
  if (driveDirection != 'N')
  driveDirection = 'L';
};

byte Drive:: isAutonomous() {
  return autonomous;
};


void Drive::driveCompReset () {
    Right_Comp =  rightCompDefault;
    // currently only changing right wheel - Left is const
    //Left_Comp = leftCompDefault;
    
  }
  
  void Drive::rightCompUp () {
  
    if (Right_Comp >254)
    // Don't let right comp go over max value 255
    
    Left_Comp = Left_Comp - 1;
    else    
    // if at max vlaue then reduce left comp
     Right_Comp = Right_Comp + 1;
    
     
  }
  
  void Drive::rightCompDown () {
  
  Right_Comp = Right_Comp - 1;
  }
