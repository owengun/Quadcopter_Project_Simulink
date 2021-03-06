#include <Wire.h>
#include <NMEAGPS.h>
#include <GPSport.h>
#include "BMP085.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "MS5611.h"
BMP085 pressure_m;
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
NMEAGPS gps;
gps_fix fix;

int32_t x = 0;
int32_t y = 0;
int32_t x_i = 0;
int32_t y_i = 0;

#define LED_PIN 13
bool blinkState = false;
void setup(){
  gpsPort.begin( 9600 );
  Serial.begin(115200);
  Wire.begin();

  pinMode(LED_PIN, OUTPUT);
  pressure_m.loadCalibration();


}
void loop()
{
  while(gps.available(gpsPort)) {
    getGPSdata();
    if (x_i == 0 && y_i == 0) {
      if (fix.longitudeL() != 0 || fix.latitudeL() != 0) {
        x_i = fix.longitudeL();
        y_i = fix.latitudeL();
        Serial.println(x_i);
        Serial.println(y_i);
        }
    }

    
      }


  Serial.print("x: ");
  Serial.print(x);
  Serial.print(F("   "));
  Serial.print("y: ");
  Serial.print(y);
  Serial.print(F("   "));
  
  
//  float temperature = pressure_m.getTemperatureC();
//  float pressure = pressure_m.getPressure();
//  float altitude = pressure_m.getAltitude(pressure);
//  Serial.print("Temperature: ");
//  Serial.print(temperature, 2);
//  Serial.println("deg C");
//  Serial.print("Pressure: ");
//  Serial.print(pressure, 0); 
//  Serial.println(" Pa");
//  Serial.print("Altitude: ");
//  Serial.print(altitude, 2); 
//  Serial.println(" M");
//  Serial.println();
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    Serial.print("a/g:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\t");
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.println(gz);

    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}

static void getGPSdata(){
  while(gps.available(gpsPort)) {
  fix = gps.read();
  x = fix.longitudeL();
  y = fix.latitudeL();
  }

  
 }
