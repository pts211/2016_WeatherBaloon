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
BigRedBee brb(&Serial2);
OpenLogger L(&Serial3);
TemperatureSensor tempSensor(A0, "Inside");
TemperatureSensor tempSensor02(A4, "Outside");
HumiditySensor humidity(A2, "Humidity");
BarometricSensor barometer("Pressure");

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
  brb.init();
  L.init();
  Serial.begin(9600);

  olog("********************\n");
  olog("INITILIZING... DONE.\n");
  olog("********************\n");
  
  humidity.init();
  barometer.init();
  /*
  String headings = tempSensor.printColHeadings() + ", " 
                  + tempSensor02.printColHeadings() + ", " 
                  + humidity.printColHeadings() + ", " 
                  + barometer.printColHeadings();
  ologln(headings);
  */

  ologln(brb.printColHeadings());
}
 
void loop()
{

  brb.poll();

  brb.print();
  
  //if( brb.read() ){
    //ologln( brb.print() );
  //}

  //Serial.println(barometer.print());

  //String reading = tempSensor.printWithLabels() + ", " 
  //               + tempSensor02.printWithLabels() + ", " 
  //               + humidity.printWithLabels() + ", " 
  //               + barometer.printWithLabels();

  String reading = tempSensor.print() + ", " 
                 + tempSensor02.print() + ", " 
                 + humidity.print() + ", " 
                 + barometer.print();
  //ologln(reading);

  delay(500);
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
