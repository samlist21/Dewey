// Include for compass
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_LSM303_U.h>
#include "math.h"
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);


byte localHeadingCounter =0;
#define HEADINGARRAY 10
float headingArray[HEADINGARRAY];
float headingAverage();
void addHeading(float heading);
float headingDiff( float, float);
void displayCompassDetails(void);
void displayAccelDetails(void);
void displayHeading(void);
void getAccel();
float currentHeadingVal;
float accel_x = 0;
float accel_y = 0;
float accel_z =0;
float xyz_Mag = 0;
boolean compassWorking = false;
long compassCounter=0;

int wait_compass = 250;  //set compass reading  wait  time
unsigned long compassMillis = millis();

int wait_accel = 5000;  //set accel reading  wait  time
unsigned long accelMillis = millis();

 boolean compassInit() {
    // Detect Compass
    
    boolean localCompassEnabled =true;
    boolean localAccelEnabled =true;
    
  /* Initialise the sensor */
  if (!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    localCompassEnabled = false;
    displayCompassDetails();
    
  } else {
    Serial.println("Magnetometer Test -X -Z"); Serial.println("");
    localCompassEnabled = true;
  
  
    /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    localAccelEnabled = false;
  } else {
    displayAccelDetails();}
  
  }
  compassWorking = localCompassEnabled;
  return localCompassEnabled;
}

void addHeading(float heading){
 // Display avererage everytime one is added.  This can be lots if turend on. 
  // float localAVG = headingAverage();
//  if (headingDiff(localAVG, heading)< 30){
  headingArray[localHeadingCounter] = heading;
          if (localHeadingCounter<HEADINGARRAY-1)
            localHeadingCounter++;
          else
            localHeadingCounter=0;
//}
//else {
//Serial.print("Bad heading reading ");
//Serial.print(heading);
//Serial.print(", Average reading");
//Serial.println(localAVG);

//}


}

float  headingDiff(float startHeading, float newHeading){

     float difference = fmod( (newHeading - startHeading +180),  360) -180;
   return difference;
}


float headingAverage(){

          float localHeadingSum, localHeadingAvg;
          //float localHeadingAvg = (headingArray[0]+headingArray[1]+headingArray[2])/3;
          
          for (int i=0; i<HEADINGARRAY; i++){
           
            localHeadingSum += headingArray[i]; 
            
          }
          localHeadingAvg = localHeadingSum /HEADINGARRAY;
          
          Serial.print(" local  Average: ");
          Serial.println(localHeadingAvg);
 
  
  return localHeadingAvg;
}


float compass(){
  float heading = 0;
  if (compassWorking){
   /* Get a new sensor event */
   // Used to get the compass right now.
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;
  // Calculate the angle of the vector y,x
  heading = (atan2(-event.magnetic.y, event.magnetic.x) * 180) / Pi;
  currentHeadingVal = heading;
  // Normalize to 0-360
  //Serial.print("Pre- Compass Heading: ");
  // displayHeading();
  
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  //Serial.print("   Compass Heading: ");
  //Serial.println(heading);
        
    // Add heading to the average
    addHeading(heading);
  }
  
  return heading;
}

void displayCompassDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
 
}

void displayAccelDetails(){
  
    /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("XYZ mag: "); Serial.print(xyz_Mag); Serial.print(",  ");
  Serial.print("X: "); Serial.print(accel_x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(accel_y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(accel_z); Serial.print("  ");Serial.println("m/s^2 ");
}


void compassTime(unsigned long nowMillis6){
    // Do not EVER Put anything here - The gets run 1000 tiems a second.
     // check mills and do this every 60 ms  using wait_compass above.
    if (nowMillis6 - compassMillis >= wait_compass) {

    // save the last time you took a compass reading
    compassMillis = nowMillis6;
    currentHeadingVal = compass();
    
         compassCounter++;
     if (compassCounter > 10){
      // Serial.println("Compass working");
       displayHeading();
       compassCounter =0;
    }
  
}
}


void accelTime(unsigned long nowMillis9){
    // Do not EVER Put anything here - The gets run 1000 tiems a second.
     // check mills and do this every 60 ms  using wait_compass above.
    if (nowMillis9 - accelMillis >= wait_accel) {
          accelMillis = nowMillis9;
      getAccel();
    }
  
}


void getAccel(){
    /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);
  
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
  
  xyz_Mag = sqrt(x*x + y*y + z*z);
 
}

void displayHeading(){
     Serial.print("Current Heading=");
    Serial.println(currentHeadingVal);  
}
