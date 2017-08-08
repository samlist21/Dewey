
long encoderRightCount = 0;
long encoderLeftCount = 0;
float encoderRightRate = 0;
float encoderLeftRate = 0;
boolean encoderRightState;
boolean encoderLeftState;
boolean encoderRightPrevious = false;
boolean encoderLeftPrevious = false;
boolean encoderChange = false;

unsigned long encoderMillisPast = millis();
unsigned long encoderMillis = 0;

int inReg;


void setupEncoder(){
  
  
  
  DDRB= B00000000;
  
}

int encoderDiff() {
	
	// Positive is left wheel is faster that right - turning right positive degrees
	// Negative is right wheel is faster that left - turning left negative degrees
	
	return (encoderLeftCount - encoderRightCount);
	
}

void printEncoderChange(){
	// Print current State (too fast)
	// Serial.print ("Left State=");
	// Serial.print (encoderLeftState);
	// Serial.print ("Right State=");
	// Serial.print (encoderRightState);

		// Print current Diff 
		Serial.print (" Encoder Diff=");
		Serial.print (encoderDiff());

		// Print current Rate 
		Serial.print (" Left Rate=");
		Serial.print (encoderLeftRate);
		Serial.print (" Right Rate=");
		Serial.print (encoderRightRate);

		// Print current Count 
		Serial.print (" Left count=");
		Serial.print (encoderLeftCount);
		Serial.print (" Right count=");
		Serial.println (encoderRightCount);
   
  
}

void readEncoder(){
	int inReg = PINB
	encoderMills = millis() - encoderMillisPast;
	
	encoderMillisPast  = millis();
	
 encoderRightState = inReg &  B00000001;
 encoderLeftState = (inReg &  B00000010)>>1;
  
 if (encoderRightState != encoderRightPrevious){
   encoderRightCount++;
   encoderChange = true;
   encoderRightPrevious = encoderRightState;
 }
   
   if (encoderLeftState != encoderLeftPrevious){
   encoderLeftCount++;
   encoderChange = true;
   encoderLeftPrevious = encoderLeftState;
 }
   
   encoderLeftRate = encoderLeftCount / encodeMills;
   encoderRightRate = encoderRightCount / encodeMills;
   
   
   if (encoderChange){
     encoderChange = false;
     printEncoderChange();
     }
   
 
 
 
  
}




void encoderClear(){
  encoderLeftCount =0;
  encoderRightCount=0;
}
  
  
