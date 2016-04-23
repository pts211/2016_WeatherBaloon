#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>

#include "TemperatureSensor.h"
#include "BarometricSensor.h"
#include "HumiditySensor.h"
#include "BigRedBee.h"
#include "OpenLogger.h"

//CONSTANTS

//SERIAL
const int BUFFLENGTH = 40;
String commandBuffer = "";
String s3_commandBuffer = "";

//INPUTS
BigRedBee brb(&Serial3);
OpenLogger L(&Serial1);
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
  L.init();
  Serial.begin(9600);

  olog("********************\n");
  olog("INITILIZING... DONE.\n");
  olog("********************\n");
  
  humidity.init();
  barometer.init();
}
 
void loop()
{

  //Serial.println(barometer.print());

  //String reading = tempSensor.printWithLabels() + ", " 
  //               + tempSensor02.printWithLabels() + ", " 
  //               + humidity.printWithLabels() + ", " 
  //               + barometer.printWithLabels();

  String reading = tempSensor.print() + ", " 
                 + tempSensor02.print() + ", " 
                 + humidity.print() + ", " 
                 + barometer.print();
  ologln(reading);

  delay(100);
 }

 void olog(String txt)
 {
  Serial.print(txt);
  L.log(txt);
 }

 void ologln(String txt)
 {
  Serial.println(txt);
  L.logln(txt);
 }
