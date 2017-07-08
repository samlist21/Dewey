#include <Wire.h>

#include <Adafruit_BMP085_U.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_L3GD20.h>
#include <Adafruit_10DOF.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include <Adafruit_LSM303_U.h>

Adafruit_10DOF dof = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(12345);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12346);

void setup(void)
{
  Serial.begin(9600);
     if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected accel... Check your wiring!");
    while(1);
  }
    if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected mag ... Check your wiring!");
    while(1);
  }
}

void loop(void)
{
  sensors_event_t accel_event;
  sensors_vec_t   orientation;
  sensors_event_t mag_event;

//  accel.getEvent(&accel_event);
//  if (dof.accelGetOrientation(&accel_event, &orientation))
//  {
//    Serial.println("--------------------------------------------------------");
//    Serial.println(orientation.pitch);
//    Serial.println(orientation.roll);
//    Serial.print(orientation.heading);
//  }
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
  {
    Serial.print(F("Heading: \n"));
    Serial.print(orientation.heading);
    Serial.print(F("; "));
  }
}

