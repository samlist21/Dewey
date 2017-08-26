// Interrupt driven Encoder Program for FFL Dewey Robot
// Author Ken Samuelson 
//  Date started 8/26/2017
// Last update by Ken Samuelson 8/26/2017
// Copyright Unpublished work Ken Samuelson 2017 all rights reserved.


long encoderRightCount = 0;
long encoderLeftCount = 0;
float encoderRightRate = 0;
float encoderLeftRate = 0;
volatile boolean encoderRightState;
volatile boolean encoderLeftState;
boolean encoderRightPrevious = false;
boolean encoderLeftPrevious = false;
//boolean encoderLeftChange = false;  // Now a Function
//boolean encoderRightChange = false;  // Now a Function
void encoderLeftChange();  // Now a Function
void encoderRightChange();   // Now a Function
volatile boolean encoderChange = false;

volatile unsigned long encoderRightResults[10];
volatile unsigned long encoderLeftResults[10];

char encodeStrBuff[15] = {'Hello'};

const int rightEncode =2;   //int0
const int leftEncode =3;     //int1

int wait_encoder = 2000;  //set compass reading  wait  time
unsigned long encoderReadMicros = 0;
unsigned long encoderReadMillis = 0;

unsigned long encoderMillisPast = millis();
volatile unsigned long encoderMicrosLeft = millis();
volatile unsigned long encoderMicrosRight = millis();
volatile unsigned long encoderMicrosLeftPrevious = millis();
volatile unsigned long encoderMicrosRightPrevious = millis();

// Old funciton declarations

volatile unsigned long encoderMillisLeft = millis();
volatile unsigned long encoderMillisRight = millis();
volatile unsigned long encoderMillisLeftPrevious = millis();
volatile unsigned long encoderMillisRightPrevious = millis();


unsigned long encoderMillis = 0;

int printCounter=0;

int inReg;


void setupEncoder(){
  Serial.println("Encoder Setup Begin");
  
    pinMode(rightEncode, INPUT);
    pinMode(leftEncode, INPUT);
    
    attachInterrupt(0,encoderRightChange,CHANGE);  // Right encoder  Pin2
    attachInterrupt(1,encoderLeftChange,CHANGE);  // Left encoder  Pin3    

  
//  DDRB= B00000000;
  Serial.println("Encoder Setup complete");
  
}

int encoderDiff() {
	
	// Positive is left wheel is faster that right - turning right positive degrees
	// Negative is right wheel is faster that left - turning left negative degrees
	
	return (encoderLeftCount - encoderRightCount);
	
}

void displayEncoderChange(){
	// Print current State (too fast)
	// Serial.print ("Left State=");
	// Serial.print (encoderLeftState);
	// Serial.print ("Right State=");
	// Serial.print (encoderRightState);

		// Print current Diff 
		Serial.print (" Encoder Diff=");
		Serial.print (encoderDiff());
		Serial.print (", MillsR=");
		Serial.print (encoderMillisRight);
		Serial.print (", MillsL=");
		Serial.print (encoderMillisLeft);
   encoderRightRate = encoderMillisRight/1000;
   encoderLeftRate = encoderMillisLeft/1000;
		// Print current Rate 
         dtostrf(encoderLeftRate, 4, 2, encodeStrBuff);
		Serial.print (" LRate=");
		Serial.print (encodeStrBuff);

         dtostrf(encoderRightRate, 4, 2, encodeStrBuff);
		Serial.print (" RRate=");
		Serial.print (encodeStrBuff);

		// Print current Count 
		Serial.print (" LCount=");
		Serial.print (encoderLeftCount);
		Serial.print (" RCount=");
		Serial.println (encoderRightCount);
   

   		Serial.print (" RArray=");
       for (int i = 0;i<10;i++){
		Serial.print (encoderRightResults[i]);
                Serial.print (", ");
                 }
                Serial.print(", Cnt=");
                Serial.println(encoderRightCount);
                
                Serial.print (" LArray=");
       for (int j = 0;j<10;j++){
		Serial.print (encoderLeftResults[j]);
                Serial.print (", ");
                 }
                Serial.print(", Cnt=");
                Serial.println(encoderLeftCount);

//		// Print current Count 
//		Serial.print (" LCount=");
//		Serial.print (encoderLeftCount);
//		Serial.print (" RCount=");
//		Serial.println (encoderRightCount);
  
}

void readEncoder(){
	 int inReg = PINB;
	encoderMillis = millis();
	
 encoderRightState = inReg &  B00000001;
 encoderLeftState = (inReg &  B00000010)>>1;
  
 if (encoderRightState != encoderRightPrevious){
   encoderRightPrevious = encoderRightState;
   encoderRightCount++;
   encoderChange = true;
   encoderMillisRight = encoderMillis - encoderMillisRightPrevious;

   encoderMillisRightPrevious = encoderMillis;
 }
   
   if (encoderLeftState != encoderLeftPrevious){
     encoderLeftPrevious = encoderLeftState;
   encoderLeftCount++;
   encoderChange = true;
   encoderMillisLeft = encoderMillis - encoderMillisLeftPrevious;

   encoderMillisLeftPrevious = encoderMillis;
 }
   
//   encoderLeftRate = encoderLeftCount / encoderMillis;
//   encoderRightRate = encoderRightCount / encoderMillis;
   
   
   if (encoderChange){
     // For every 20 changes in encoder vlaue print out the status
     printCounter++;
     if (printCounter > 40){
       displayEncoderChange();
       printCounter =0;
     }
     else{
     encoderChange = false;
     
     }
   
 
  }
 
  
}




void encoderClear(){
  encoderLeftCount =0;
  encoderRightCount=0;
  Serial.println("Encoder Cleared");
}
  
  
  
  void encoderTime(unsigned long nowMillis3){
    // Do not EVER Put anything here - The gets run 1000 tiems a second.
     // check mills and do this every 60 ms  using wait_compass above.
    if (nowMillis3 - encoderReadMillis >= wait_encoder) {
          encoderReadMillis = nowMillis3;
     // readEncoder();
      
//     if (encoderChange){
     // For every 20 changes in encoder vlaue print out the status
     printCounter++;
     if (printCounter > 1){
       displayEncoderChange();
       printCounter =0;
     }
     else{
     encoderChange = false;
     
     }
   
 
//  }
      
    }
  
}


void encoderRightChange(){
	 
  unsigned long encoderMicros = micros();
  encoderRightState = !encoderRightState;
  
   encoderRightCount++;

   encoderMicrosRight = encoderMicros - encoderMicrosRightPrevious;

   encoderRightResults[encoderRightCount%10] = encoderMicrosRight;

   encoderMicrosRightPrevious = encoderMicros;
   encoderChange = true;
   
 }
  
  
  void encoderLeftChange(){
	 
  unsigned long encoderMicros = micros();
  encoderLeftState = !encoderLeftState;
  
   encoderLeftCount++;

   encoderMicrosLeft = encoderMicros - encoderMicrosLeftPrevious;

   encoderLeftResults[encoderLeftCount%10] = encoderMicrosLeft;

   encoderMicrosLeftPrevious = encoderMicros;
   encoderChange = true;
   
 }
   

 
  

