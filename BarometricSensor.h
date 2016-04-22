#ifndef BAROMETRICSENSOR_H
#define BAROMETRICSENSOR_H

#include <Arduino.h>
#include "Barometer.h"

class BarometricSensor
{
private:
  Barometer m_barometer;
  float m_pressure;
  
public:
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
  //Postconditions:  Reads sensor, returns the temperature.
  float getTemp()
  {
    return m_barometer.bmp085GetTemperature(m_barometer.bmp085ReadUT()); //Get the temperature, bmp085ReadUT MUST be called first
  }
  
  //Function:  getPressure()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the pressure.
  float getPressure()
  {
    m_pressure = m_barometer.bmp085GetPressure(m_barometer.bmp085ReadUP());//Get the temperature
    return m_pressure;
  }
  
  //Function:  getAltitude()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the altitude.
  float getAltitude()
  {
    return m_barometer.calcAltitude(m_pressure); //Uncompensated calculation - in Meters 
  }
  
  //Function:  getATM()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, returns the atmospheric pressure.
  float getATM()
  {
    return m_pressure / 101325;
  }

  //Function: print()
  //Description: prints out the sensor data comma delimitted: "temp, pressure, altitude, atm;"
  String print()
  {
    return String(getTemp()) + ", " + String(getPressure()) + ", " + String(getAltitude()) + ", " + String(getATM()) + "; ";
  }
};

#endif
