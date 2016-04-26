#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>

#include "TemperatureSensor.h"
#include "BarometricSensor.h"
#include "HumiditySensor.h"
#include "VoltageSensor.h"
#include "GeigerCounter.h"
#include <avr/pgmspace.h>

/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
//Start of Configuration

/* TODO Recommend setting FLIGHT_MODE to true for launch.
 *      This will disable the printing that happens to the regular serial port 
 *      in hopes of avoiding potential problems, reducing the Arduino's load, etc.
 */
#define FLIGHT_MODE false
#define GPS_CONN_ENABLED false

/* Tick Interval
 *  The arduino will log data every tick, set in ms.
 */
#define TICK_INTERVAL 5000

/* Battery Voltage Monitor - Resistor Values
 *  The resistor values used for our voltage divider calcuation of
 *  the supply batteries power.
 */
#define R1 21770
#define R2 9800

//End of Configuration
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
#if GPS_CONN_ENABLED
#include "BigRedBee.h"
#endif

 
//DEVICES
#if GPS_CONN_ENABLED
  BigRedBee brb(&Serial2);
#endif
HardwareSerial *openLog = &Serial1;
GeigerCounter geiger(&Serial3);
TemperatureSensor tempSensor(A0, "Inside");
TemperatureSensor tempSensor02(A4, "Outside");
HumiditySensor humidity(A2, "Humidity");
BarometricSensor barometer("Pressure");
VoltageSensor vsBatt(A14, "Battery");
VoltageSensor vsLemons(A15, "Lemons");

unsigned int currentMillis = 0;
unsigned int previousMillis = 0;
unsigned int tick_count = 0;

void setup()
{
  Serial.begin(9600);
  openLog->begin(9600);
  
  #if GPS_CONN_ENABLED
    brb.init();
  #endif
  geiger.init();
  humidity.init();
  barometer.init();
  vsBatt.init();
  vsLemons.init();

  vsBatt.setResistors(R1, R2);

  #if !FLIGHT_MODE
  Serial.print(F("Tick, Runtime, "));
  #if GPS_CONN_ENABLED
    brb.printColHeadings(openLog, true);
  #endif
  tempSensor.printColHeadings(&Serial, true);
  tempSensor02.printColHeadings(&Serial, true);
  humidity.printColHeadings(&Serial, true);
  barometer.printColHeadings(&Serial, true);
  vsBatt.printColHeadings(&Serial, true);
  vsLemons.printColHeadings(&Serial, true);
  geiger.printColHeadings(&Serial);
  Serial.println();
  #endif
  
  openLog->print(F("Tick, Runtime, "));
  #if GPS_CONN_ENABLED
    brb.printColHeadings(openLog, true);
  #endif
  tempSensor.printColHeadings(openLog, true);
  tempSensor02.printColHeadings(openLog, true);
  humidity.printColHeadings(openLog, true);
  barometer.printColHeadings(openLog, true);
  vsBatt.printColHeadings(openLog, true);
  vsLemons.printColHeadings(openLog, true);
  geiger.printColHeadings(openLog);
  openLog->println();
}
 
void loop()
{
  geiger.poll();
  vsBatt.poll();
  vsLemons.poll();
  #if GPS_CONN_ENABLED
    brb.poll();
  #endif

  currentMillis = millis();
  if(currentMillis - previousMillis > TICK_INTERVAL)
  {
    // ---------- USB SERIAL OUTPUT ----------
    #if !FLIGHT_MODE
    Serial.print(tick_count);
    Serial.print(F(", "));
    Serial.print(getRuntime());
    Serial.print(F(", "));
    #if GPS_CONN_ENABLED
      brb.print(&Serial, true);
    #endif
    tempSensor.printWithLabels(&Serial, true);
    tempSensor02.printWithLabels(&Serial, true);
    humidity.printWithLabels(&Serial, true);
    barometer.printWithLabels(&Serial, true);
    vsBatt.printWithLabels(&Serial, true);
    vsLemons.printWithLabels(&Serial, true);
    geiger.print(&Serial);
    Serial.println();
    #endif


    // ---------- OPEN LOG OUTPUT ----------
    openLog->print(tick_count++);
    openLog->print(F(", "));
    openLog->print(getRuntime());
    openLog->print(F(", "));
    #if GPS_CONN_ENABLED
      brb.print(openLog, true);
    #endif
    tempSensor.print(openLog, true);
    tempSensor02.print(openLog, true);
    humidity.print(openLog, true);
    barometer.print(openLog, true);
    vsBatt.print(openLog, true);
    vsLemons.print(openLog, true);
    geiger.print(openLog);
    openLog->println();

    
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

