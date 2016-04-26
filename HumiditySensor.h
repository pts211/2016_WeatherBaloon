#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include <Arduino.h>
//#include "libraries/DHT.h"
#include "DHT.h"

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTTYPE DHT21   // DHT 21 (AM2301)

class HumiditySensor
{
private:
  DHT * dht;
  float m_temp;
  float m_humidity;
  String m_id;
  
public:
  //HumiditySensor constructor
  HumiditySensor(const int analog_port, const String id = "undef")
  {
    dht = new DHT(analog_port, DHTTYPE);
    m_id = id;
  }

  //Function:  init()
  //Description:  initilizes the PIN to be used for sensor.
  //Preconditions:  sensor pin has been set.
  //Postconditions:  The pinMode method is called and sets the sensor to input.
  void init()
  {
    dht->begin();
  }

  //Function:  getTemperature()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the temperature (celsius).
  float getTemp()
  {
    m_temp = dht->readTemperature();
    m_temp = (m_temp * 9.0) / 5.0 + 32; //Farenheit
    return isnan(m_temp) ? 0 : m_temp;
  }
  
  //Function:  getPressure()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the humidity (percentage).
  float getHumidity()
  {
    m_humidity = dht->readHumidity();
    return (isnan(m_humidity)) ? 0 : m_humidity;
  }
  
  void printColHeadings(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(F("Temp("));
    s->print(m_id);
    s->print(F(") (F), Humidity (%)"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void print(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(getTemp());
    s->print(F(", "));
    s->print(getHumidity());
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void printWithLabels(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(getTemp());
    s->print(F(" *F, "));
    s->print(getHumidity());
    s->print(F(" %"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
};

#endif
