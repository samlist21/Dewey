
long encoderRightCount = 0;
long encoderLeftCount = 0;
float encoderRightRate = 0;
float encoderLeftRate = 0;
boolean encoderRightState;
boolean encoderLeftState;
boolean encoderRightPrevious = false;
boolean encoderLeftPrevious = false;
boolean encoderLeftChange = false;
boolean encoderRightChange = false;
boolean encoderChange = false;

unsigned long encoderMillisPast = millis();
unsigned long encoderMillisLeft = millis();
unsigned long encoderMillisRight = millis();
unsigned long encoderMillis = 0;

int printCounter=0;

int inReg;


void setupEncoder(){
  
  
  
  DDRB= B00000000;
  
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

		// Print current Rate 
		Serial.print (" LRate=");
		Serial.print (encoderLeftRate);
		Serial.print (" RRate=");
		Serial.print (encoderRightRate);

		// Print current Count 
		Serial.print (" LCount=");
		Serial.print (encoderLeftCount);
		Serial.print (" RCount=");
		Serial.println (encoderRightCount);
   
  
}

void readEncoder(){
	 int inReg = PINB;
//	encoderMillis = millis() - encoderMillisPast;
	
//  if (encoderMillis >250){

//	encoderMillisPast  = millis();
	
 encoderRightState = inReg &  B00000001;
 encoderLeftState = (inReg &  B00000010)>>1;
  
 if (encoderRightState != encoderRightPrevious){
   encoderRightCount++;
   encoderChange = true;
   encoderMillisRight = millis() - encoderMillisRight;
   encoderRightRate = 1 / encoderMillisRight;
   encoderRightPrevious = encoderRightState;
 }
   
   if (encoderLeftState != encoderLeftPrevious){
   encoderLeftCount++;
   encoderChange = true;
   encoderMillisLeft = millis() - encoderMillisLeft;
   encoderLeftRate = 1 / encoderMillisLeft;
   encoderLeftPrevious = encoderLeftState;
 }
   
//   encoderLeftRate = encoderLeftCount / encoderMillis;
//   encoderRightRate = encoderRightCount / encoderMillis;
   
   
   if (encoderChange){
     printCounter++;
     if (printCounter >20){
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
}
  
  
