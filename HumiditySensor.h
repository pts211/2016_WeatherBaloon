#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include <Arduino.h>
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
  
public:
  //HumiditySensor constructor
  HumiditySensor(const int analog_port)
  {
    dht = new DHT(analog_port, DHTTYPE);
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

  //Function: print()
  //Description: prints out the sensor data comma delimitted: "temp, pressure, altitude, atm;"
  String print()
  {
    return String(getTemp()) + ", " + String(getHumidity());
  }

  String printWithLabels()
  {
    return String(getTemp()) + " *C, " + String(getHumidity()) + " %";
  }
};

#endif
