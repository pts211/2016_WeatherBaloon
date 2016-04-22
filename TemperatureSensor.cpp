#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const int sPin)
{
  m_sensPin = sPin;
}

float TemperatureSensor::getTemp()
{
  m_rawVal = analogRead(m_sensPin);

  m_R = 1023.0/((float)m_rawVal) - 1.0;  
  m_R *= R0;
  m_tempDegC = 1.0/(log(m_R/R0)/B+1/298.15)-273.15; //convert to temperature via datasheet;

  return m_tempDegC;
}

int TemperatureSensor::getPin()
{
  return m_sensPin;
}
