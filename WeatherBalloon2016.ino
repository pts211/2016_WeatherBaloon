#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>

#include "TemperatureSensor.h"
#include "BarometricSensor.h"
#include "HumiditySensor.h"

//CONSTANTS

//SERIAL
const int BUFFLENGTH = 40;
String commandBuffer = "";
String s3_commandBuffer = "";

//VARIABLES
#define DHTPIN A0     // what pin we're connected to

//INPUTS
TemperatureSensor tempSensor(A0);
TemperatureSensor tempSensor02(A4);
HumiditySensor humidity(A2);
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
  Serial.print("Weather Baloon Monitoring System Initilizing...");
  
  humidity.init();
  barometer.init();

  Serial.println("done!");
}
 
void loop()
{

  //Serial.println(barometer.print());

  String reading = tempSensor.printWithLabels() + ", " 
                 + tempSensor02.printWithLabels() + ", " 
                 + humidity.printWithLabels() + ", " 
                 + barometer.printWithLabels();
  Serial.println(reading);

  delay(100);
 }
