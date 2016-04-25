#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>

#include "TemperatureSensor.h"
#include "BarometricSensor.h"
#include "HumiditySensor.h"
#include "VoltageSensor.h"
#include "GeigerCounter.h"
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


//DEVICES
HardwareSerial *openLog = &Serial1;
GeigerCounter geiger(&Serial3);
TemperatureSensor tempSensor(A0, "Inside");
TemperatureSensor tempSensor02(A4, "Outside");
HumiditySensor humidity(A2, "Humidity");
BarometricSensor barometer("Pressure");
VoltageSensor vsBatt(A6, "Battery");
VoltageSensor vsLemons(A7, "Lemons");

unsigned int currentMillis = 0;
unsigned int previousMillis = 0;
unsigned int tick_count = 0;

/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
//Start of Configuration

const unsigned int TICK_INTERVAL = 5000;

//End of Configuration
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
 
void setup()
{
  Serial.begin(9600);
  openLog->begin(9600);
  
  geiger.init();
  humidity.init();
  barometer.init();
  vsBatt.init();
  vsLemons.init();

  tempSensor.printColHeadings(openLog, true);
  tempSensor02.printColHeadings(openLog, true);
  humidity.printColHeadings(openLog, true);
  barometer.printColHeadings(openLog, true);
  vsBatt.printColHeadings(openLog, true);
  vsLemons.printColHeadings(openLog, true);
  geiger.printColHeadings(openLog);
}
 
void loop()
{
  geiger.poll();
  vsBatt.poll();
  vsLemons.poll();

  currentMillis = millis();
  if(currentMillis - previousMillis > TICK_INTERVAL)
  {
    Serial.print(F("Tick: "));
    Serial.print(tick_count++);
    Serial.print(F(", Runtime: "));
    Serial.print(getRuntime());
    Serial.print(F(", "));
    tempSensor.printWithLabels(&Serial, true);
    tempSensor02.printWithLabels(&Serial, true);
    humidity.printWithLabels(&Serial, true);
    barometer.printWithLabels(&Serial, true);
    vsBatt.printWithLabels(&Serial, true);
    vsLemons.printWithLabels(&Serial, true);
    geiger.print(&Serial);
    
    /*
    openLog->print(F("Tick: "));
    openLog->print(tick_count++);
    openLog->print(F(", Runtime: "));
    openLog->print(getRuntime());
    openLog->print(F(", "));
    tempSensor.printWithLabels(openLog, true);
    tempSensor02.printWithLabels(openLog, true);
    humidity.printWithLabels(openLog, true);
    barometer.printWithLabels(openLog, true);
    vsBatt.printWithLabels(openLog, true);
    vsLemons.printWithLabels(openLog, true);
    geiger.print(openLog);
    */
    /*
    openLog->print(F("Tick: "));
    openLog->print(tick_count++);
    openLog->print(F(", Runtime: "));
    openLog->print(getRuntime());
    openLog->print(F(", "));
    tempSensor.print(openLog, true);
    tempSensor02.print(openLog, true);
    humidity.print(openLog, true);
    barometer.print(openLog, true);
    vsBatt.print(openLog, true);
    vsLemons.print(openLog, true);
    geiger.print(openLog);
    */
    previousMillis = currentMillis;
  }
 }

 String getRuntime()
{
  unsigned long t = millis()/1000;
  static char str[12];
  long h = t / 3600;
  t = t % 3600;
  int m = t / 60;
  int s = t % 60;
  sprintf(str, "%04ld:%02d:%02d", h, m, s);
  return String(str);
}

