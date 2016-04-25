#ifndef BAROMETRICSENSOR_H
#define BAROMETRICSENSOR_H

#include <Arduino.h>
//#include "libraries/Barometer.h"
#include "Barometer.h"

class BarometricSensor
{
private:
  Barometer m_barometer;
  String m_id;
  float m_pressure;
  
public:

  BarometricSensor(const String id = "undef")
  {
    m_id = id;
  }
  //Function:  init()
  //Description:  initilizes the PIN to be used for sensor.
  //Preconditions:  sensor pin has been set.
  //Postconditions:  The pinMode method is called and sets the sensor to input.
  void init()
  {
    m_pressure = 1;
    m_barometer.init();
  }

  //Function:  getTemperature()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the temperature (celsius).
  float getTemp()
  {
    return m_barometer.bmp085GetTemperature(m_barometer.bmp085ReadUT()); //Get the temperature, bmp085ReadUT MUST be called first
  }
  
  //Function:  getPressure()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the pressure (kb?).
  float getPressure()
  {
    m_pressure = m_barometer.bmp085GetPressure(m_barometer.bmp085ReadUP());//Get the temperature
    return m_pressure;
  }
  
  //Function:  getAltitude()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the altitude (meters).
  float getAltitude()
  {
    return m_barometer.calcAltitude(m_pressure); //Uncompensated calculation - in Meters 
  }
  
  //Function:  getATM()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the atmospheric pressure (ATM).
  float getATM()
  {
    return m_pressure / 101325;
  }

  
  void printColHeadings(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(F("Temp( "));
    s->print(m_id);
    s->print(F(") (C), Pressure (Pa), Altitude (m), ATM (atm)"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void print(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(getTemp());
    s->print(F(", "));
    s->print(getPressure());
    s->print(F(", "));
    s->print(getAltitude());
    s->print(F(", "));
    s->print(getATM());
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void printWithLabels(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(getTemp());
    s->print(F(" *C, "));
    s->print(getPressure());
    s->print(F(" Pa, "));
    s->print(getAltitude());
    s->print(F(" m, "));
    s->print(getATM());
    s->print(F(" atm"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
};

#endif
