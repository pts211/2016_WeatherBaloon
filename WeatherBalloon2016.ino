#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <MemoryFree.h>

#include "TemperatureSensor.h"
#include "BarometricSensor.h"
#include "HumiditySensor.h"
#include "BigRedBee.h"
#include "GeigerCounter.h"
#include "OpenLogger.h"
#include <avr/pgmspace.h>
 
int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
 
void StreamPrint_progmem(Print &out,PGM_P format,...)
{
  // program memory version of printf - copy of format string and result share a buffer
  // so as to avoid too much memory use
  char formatString[128], *ptr;
  strncpy_P( formatString, format, sizeof(formatString) ); // copy in from program mem
  // null terminate - leave last char since we might need it in worst case for result's \0
  formatString[ sizeof(formatString)-2 ]='\0'; 
  ptr=&formatString[ strlen(formatString)+1 ]; // our result buffer...
  va_list args;
  va_start (args,format);
  vsnprintf(ptr, sizeof(formatString)-1-strlen(formatString), formatString, args );
  va_end (args);
  formatString[ sizeof(formatString)-1 ]='\0'; 
  out.print(ptr);
}
#define Serialprint(format, ...) StreamPrint_progmem(Serial,PSTR(format),##__VA_ARGS__)
#define Streamprint(stream,format, ...) StreamPrint_progmem(stream,PSTR(format),##__VA_ARGS__)
 

//CONSTANTS

//SERIAL
const int BUFFLENGTH = 40;
String commandBuffer = "";
String s3_commandBuffer = "";

//INPUTS
GeigerCounter geiger(&Serial3);
BigRedBee brb(&Serial2);
OpenLogger L(&Serial1);
TemperatureSensor tempSensor(A0, "Inside");
TemperatureSensor tempSensor02(A4, "Outside");
HumiditySensor humidity(A2, "Humidity");
BarometricSensor barometer("Pressure");

//

/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
//Start of Configuration

uint8_t * heapptr, * stackptr;

//End of Configuration
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
 
void setup()
{
  //geiger.init();
  brb.init();
  //L.init();
  Serial.begin(9600);

  olog("********************\n");
  olog("INITILIZING... DONE.\n");
  olog("********************\n");
  
  //humidity.init();
  //barometer.init();
  /*
  String headings = tempSensor.printColHeadings() + ", " 
                  + tempSensor02.printColHeadings() + ", " 
                  + humidity.printColHeadings() + ", " 
                  + barometer.printColHeadings();
  ologln(headings);
  */

  //ologln(brb.printColHeadings());
  ologln(geiger.printColHeadings());
}
 
void loop()
{
  //check_mem();
  /*
  Serial.print("heap_size: ");
  Serial.print(*(heapptr));
  Serial.print(" stack_size: ");
  Serial.println(*(stackptr));
  */
  //geiger.poll();
  //ologln(geiger.print());
  
  
  
  //geiger.print();

  //Serialprint(" freeRAM()= %d - main loop\n", freeRam());

  //brb.poll();
  //Serial.println(brb.print());
  //Serial.println(barometer.print());

  //String reading = tempSensor.printWithLabels() + ", " 
  //               + tempSensor02.printWithLabels() + ", " 
  //               + humidity.printWithLabels() + ", " 
  //               + barometer.printWithLabels();

  //String reading = tempSensor.print() + ", " 
  //               + tempSensor02.print() + ", " 
  //               + humidity.print() + ", " 
  //               + barometer.print();
  //ologln(reading);

  //delay(5);
 }
 
 void olog(String txt)
 {
  Serial.print(txt);
  L.log(txt);
 }

 void ologln(String txt)
 {
  //Serial.println(txt);
  L.logln(txt);
 }
