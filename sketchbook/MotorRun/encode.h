
long encoderRightCount = 0;
long encoderLeftCount = 0;
boolean encoderRightState;
boolean encoderLeftState;
boolean encoderRightPrevious = false;
boolean encoderLeftPrevious = false;
boolean encoderChange = false;

int inReg;


void setupEncoder(){
  
  
  
  DDRB= B00000000;
  
}

void printEncoderChange(){
  Serial.print ("Left State=");
  Serial.print (encoderLeftState);
    Serial.print ("Right State=");
  Serial.println (encoderRightState);
  
    Serial.print ("Left count=");
  Serial.print (encoderLeftCount);
    Serial.print ("Right count=");
  Serial.println (encoderRightCount);
}

void readEncoder(){
 encoderRightState = PINB &  B00000001;
 encoderLeftState = (PINB &   B00000010)>>1;
  
 if (encoderRightState != encoderRightPrevious){
   encoderRightCount++;
   encoderChange = true;
   encoderRightPrevious = encoderRightState;
 }
   
   if (encoderLeftState != encoderLeftPrevious){
   encoderRightCount++;
   encoderChange = true;
   encoderLeftPrevious = encoderLeftState;
 }
   
   if (encoderChange){
     encoderChange = false;
     printEncoderChange();
     }
   
 
 
 
  
}




void encoderClear(){
  encoderLeftCount =0;
  encoderRightCount=0;
}
  
  
