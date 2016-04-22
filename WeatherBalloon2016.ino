#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>

#include "TemperatureSensor.h"
#include "BarometricSensor.h"

//CONSTANTS

//SERIAL
const int BUFFLENGTH = 40;
String commandBuffer = "";
String s3_commandBuffer = "";

//VARIABLES
float temperature;
float pressure;
float atm;
float altitude;

//INPUTS
TemperatureSensor tempSensor(0);
BarometricSensor barometer;

//

/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
//Start of Configuration



//End of Configuration
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/

 
void setup()
{
  Serial.begin(9600);
  
  barometer.init();
}
 
void loop()
{
  // temperature = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT()); //Get the temperature, bmp085ReadUT MUST be called first
   //pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());//Get the temperature
   //altitude = myBarometer.calcAltitude(pressure); //Uncompensated calculation - in Meters 
   //atm = pressure / 101325; 

   temperature = barometer.getTemp();
   pressure = barometer.getPressure();
   altitude = barometer.getAltitude();
   atm  = barometer.getATM();

   Serial.println(barometer.print());
  /*
  Serial.print("Temperature: ");
  Serial.print(temperature, 2); //display 2 decimal places
  Serial.print("deg C | ");

  Serial.print("Pressure: ");
  Serial.print(pressure, 0); //whole number only.
  Serial.print(" Pa | ");

  Serial.print("Ralated Atmosphere: ");
  Serial.print(atm, 4); //display 4 decimal places
  Serial.print(" | ");

  Serial.print("Altitude: ");
  Serial.print(altitude, 2); //display 2 decimal places
  Serial.print(" m | ");

  
  Serial.print(" tS.temp:" + String(tempSensor.getTemp()) + " ");
  Serial.println();
  */
  delay(100);
 }
