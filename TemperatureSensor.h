#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>

class TemperatureSensor
{
private:
  const int B = 4275; // B value of the thermistor
  const float R0 = 100000.0;  // R0 = 100k
  
  int m_sensPin;
  String m_id;
  int m_rawVal; //Storing as a float to save a cast later.
  float m_R;
  float m_tempDegF;

public:

  //TemperatureSensor constructor
  TemperatureSensor(const int analog_port, const String id = "undf")
  {
    m_sensPin = analog_port;
    m_id = id;
  }

  //Function:  init()
  //Description:  initilizes the PIN to be used for sensor.
  //Preconditions:  sensor pin has been set.
  //Postconditions:  The pinMode method is called and sets the sensor to input.
  void init()
  {
    analogRead(m_sensPin);
  }
  
  //Function:  getTemperature()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, return the temperature (celsius).
  float getTemp()
  {
    m_rawVal = analogRead(m_sensPin);

    m_R = 1023.0/((float)m_rawVal) - 1.0;  
    m_R *= R0;
    m_tempDegF = 1.0/(log(m_R/R0)/B+1/298.15)-273.15; //convert to temperature via datasheet; Celsius
    m_tempDegF = (m_tempDegF * 9.0) / 5.0 + 32; //Farenheit
    
    return m_tempDegF;
  }

  //Function:  getPin()
  //Description:  Used for checking which PIN the sensor is on. 
  //Postconditions:  Returns PIN number for sensor. 
  int getPin()
  {
    return m_sensPin;
  }
  
  void printColHeadings(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(F("Temp("));
    s->print(m_id);
    s->print(F(") (F)"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void print(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(getTemp());
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void printWithLabels(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(getTemp());
    s->print(F(" *F, "));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
};

#endif
