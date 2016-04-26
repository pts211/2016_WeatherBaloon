#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

#include <Arduino.h>

class VoltageSensor
{
private:
  const int AVERAGE_SAMPLES = 20;
  
  const float ANALOG_MAX = 1023.0;
  const float VOLTAGE_MAX = 5.0;
  
  int m_sensPin;
  String m_id;
  
  float m_Vraw;
  float m_Vavg;

  int m_R1 = 0;
  int m_R2 = 1;


public:

  //VoltageSensor constructor
  VoltageSensor(const int analog_port, const String id = "undf")
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

  void setResistors(const int r1, const int r2)
  {
    m_R1 = r1;
    m_R2 = r2;
  }
  
  //Function: poll()
  //Description: updates the rolling average of the voltage over so many AVERAGE_SAMPLES.
  void poll()
  {
    m_Vraw = (float)(analogRead(m_sensPin) * (VOLTAGE_MAX / ANALOG_MAX)) * ((float)(m_R1 + m_R2)/(float)m_R2); 
    
    m_Vavg -= m_Vavg / (float)AVERAGE_SAMPLES;
    m_Vavg += m_Vraw / (float)AVERAGE_SAMPLES;
  }
  
  //Function:  getTemperature()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, return the temperature (celsius).
  float getRawVoltage()
  {
    return m_Vraw;
  }
  
  float getAverageVoltage()
  {

    return m_Vavg;
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
    s->print(F("Voltage("));
    s->print(m_id);
    s->print(F(") (V), Avg Voltage("));
    s->print(m_id);
    s->print(F(") (V)"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void print(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(m_Vraw);
    s->print(F(", "));
    s->print(m_Vavg);
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void printWithLabels(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(m_Vraw);
    s->print(F("V, "));
    s->print(m_Vavg);
    s->print(F("V"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
};

#endif
