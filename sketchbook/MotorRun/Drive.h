class Drive {
  
  const int Left_CW= 5;
  const int Left_CCW= 6;

  const int Rigth_CCW= 10;
  const int Rigth_CW= 11;
  
  const int ledPin = 13;
  
  
  //  These are positive vlaues and will compensate for the wheels
   // not tracking straight
  //   These values are subtracted from FWD and REV equally 
  // Not sure if Dewey tracks the same forward and back 
  // Need to test
  const byte Right_Comp = 4;
  const byte Left_Comp = 0;
  const byte RightBack_Comp = 0;
  const byte LeftBack_Comp = 15;  
 
   byte holdCommand;
   byte slowSpeed;
   long prevCm;
   int driveRight = 0;
   bool autonomous = false;
  
  public:
    Drive();

    void driveAutonomous();
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
  
  private:
    byte driveSpeed = 100 ;
    
    boolean hold = false;
    boolean slow = false;
    byte driveDirection = 'S';  // Start in STOP mode
    byte driveCommand = 'S';  // Start drive command STOP
    
    
    void driveBACK();

    
    void driveRIGHT();
    void driveLEFT();
        
   
  
};
  
   Drive::Drive (){
     //constructor set default speed and PINS as outputs
    driveSpeed = 128;
    pinMode(Left_CW,OUTPUT);
    pinMode(Left_CCW,OUTPUT);  
    
    pinMode(Rigth_CCW,OUTPUT);
    pinMode(Rigth_CW,OUTPUT);
   };
  
  
  void Drive::driveHold (){
    
    if (hold != true){
      // make it so this can only be called once
      // then it needs to resule before it can be called again.
      // toggle They can't be called multiple times. 

   holdCommand = driveDirection;
   driveDirection = 'S';  // set to stop
   checkValue(driveDirection);
//   Serial.print ("Hold Command=");
//   Serial.println(holdCommand);
  // Speed = speed;
    hold = true;
    }
  };

  void Drive::driveSlow (){
    
    if (slow != true){
      // make it so this can only be called once
      // then it needs to resule before it can be called again.
      // toggle They can't be called multiple times. 

   slowSpeed = driveSpeed;
   driveSpeed = 144;  // set to = to "1"
//   checkValue(driveDirection);
//   Serial.print ("Slow Command=");
//   Serial.println(slowSpeed);
  // Speed = speed;
    slow = true;
    }
  };

  void Drive::driveResume (){
       
 
     if (hold == true){ // run this casee only once after a hold
     hold = false;
     slow = false;
       driveDirection = holdCommand;
       
//       Serial.print ("Resume Command=");
//       Serial.println(driveDirection);
       
       checkValue(driveDirection);
//        Serial.println("Restarting");
      
        
        
     };
 
  // Speed = speed;
  };
  
  void Drive::runSpeed (byte amount){
  driveSpeed = amount;
  // Speed = speed;
  };
  
  byte Drive::readSpeed (){
    int driveSpeed1 = int(driveSpeed);
  byte outSpeed = (((driveSpeed1+1)/16) + byte('0') - 7);
  return byte(outSpeed);
  };
  
  
  void Drive::driveAutonomous (long cm) 
  {
	if (autonomous)
	{
		if (cm =< 15)
		{
			if (cm < cmPrev)
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
		cmPrev = cm;
	}
  };

  void Drive::driveUpdate (){
      // need to convert to case
         if (driveDirection == 'F' ){
         driveFWD();}
         
         if (driveDirection == 'B' ){
         driveBACK();}
         
         if (driveDirection == 'S' ){
         driveSTOP();}
// need to put right and left in here

// 
 
   };
   
    byte Drive::driveStatus (){
       
   return driveDirection;
   };


     void Drive::checkValue (byte value){
       
        if (hold != true) {
       // can't use range case so this is better as an if.  
      if (value >= '0' and value <= '9'){
         // remove the ascii then multipy by 16 to get speed values
        //  betweeen 127 and 255 - 1-9 setting
         driveSpeed = ((((value - '0')+6)*16)+15);
         //wanted to add 7 but woueld overrun byte before the subtraction
         //so adding then adding 15 at the end.

         driveUpdate();

         
       }
         
     
       switch(value) {
      
  
         case 'x':
         case 'X':
         driveDirection = 'S'; 
         driveSTOP();
         //exit(0);  // may not be able to or want to use exit
         // a reeset would be required to move again
         
         break;
         
         case 's':
         case 'S':
         case '0':
         
         driveDirection = 'S';
		 if (autonomous)
		 {
			autonomous = false;
		 }
         driveSTOP();
         
         break;
         
         case 'f':
         case 'F':
         
         driveDirection = 'F';
         driveFWD();
         
         break;

         case 'b':
         case 'B':
         
         driveDirection = 'B'; 
         driveBACK();
         
         break;
         
         case 'r':
         case 'R':
         
         driveDirection = 'R';
         driveRIGHT();
         
         break;
         
         case 'l':
         case 'L':
         
         driveDirection = 'L';
         driveLEFT();
		 
		 break;
		 
		 case 'a':
		 case 'A':
		 
		 autonomous = true;
		 driveAutonomous();
		 
		 break;
         
         
         default: 
         // can't so anythign here or the A-Z will nto be used. 
         
         break;
       }
 
      // can't sue raneg case so thsi si better as an if.  
      //if (value >= 'A' and value <= 'Z'){
      //   driveCommand = value;

      //   driveUpdate();
         
      // }
       
        } // end of hold 
 
   };
   

    void Drive::driveFWD (){
     // Set to reverse 
      // LEFT A Clockwise - REV - White 
      analogWrite(Left_CW,0);
      // LEFT A counter-Clockwise FWD - Green 
      analogWrite(Left_CCW,driveSpeed- Left_Comp); 
        
      // Right Counter Clockwise REV - White
      analogWrite(Rigth_CCW,0); 
      // Right Clockwise  FWD - Yellow 
      analogWrite(Rigth_CW,driveSpeed- Right_Comp);  
      
      driveDirection = 'F';
   };

  void Drive::driveBACK (){
     // Set to reverse 
      // LEFT A Clockwise - REV - White 
      analogWrite(Left_CW,driveSpeed- LeftBack_Comp);
      // LEFT A counter-Clockwise FWD - Green 
      analogWrite(Left_CCW,0); 
        
      // Right Counter Clockwise REV - White
      analogWrite(Rigth_CCW,driveSpeed - RightBack_Comp); 
      // Right Clockwise  FWD - Yellow 
      analogWrite(Rigth_CW,0);  
      //B - Back = recerse since R will be used for Right later. 
      driveDirection = 'B';
   };

    void Drive::driveSTOP (){
     // Set to reverse x
      // LEFT A Clockwise - REV - White 
      analogWrite(Left_CW,0);
      // LEFT A counter-Clockwise FWD - Green 
      analogWrite(Left_CCW,0); 
        
      // Right Counter Clockwise REV - White
      analogWrite(Rigth_CCW,0); 
      // Right Clockwise  FWD - Yellow 
      analogWrite(Rigth_CW,0);  
      driveDirection = 'S';
   };

  void Drive::driveRIGHT (){
     // Set to reverse 
      // LEFT A Clockwise - REV - White 
      analogWrite(Left_CW,0);
      // LEFT A counter-Clockwise FWD - Green 
      analogWrite(Left_CCW,driveSpeed/2); 
        
      // Right Counter Clockwise REV - White
      analogWrite(Rigth_CCW,driveSpeed/2); 
      // Right Clockwise  FWD - Yellow 
      analogWrite(Rigth_CW,0);  
      //B - Back = recerse since R will be used for Right later. 
      driveDirection = 'R';
   };
   
     void Drive::driveLEFT (){
     // Set to reverse 
      // LEFT A Clockwise - REV - White 
      analogWrite(Left_CW,driveSpeed/2);
      // LEFT A counter-Clockwise FWD - Green 
      analogWrite(Left_CCW,0); 
        
      // Right Counter Clockwise REV - White
      analogWrite(Rigth_CCW,0); 
      // Right Clockwise  FWD - Yellow 
      analogWrite(Rigth_CW,driveSpeed/2);  
      //B - Back = recerse since R will be used for Right later. 
      driveDirection = 'L';
   };
  
