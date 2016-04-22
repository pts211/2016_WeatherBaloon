#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>

class TemperatureSensor
{
private:
  const int B = 4275; // B value of the thermistor
  const float R0 = 100000.0;  // R0 = 100k
  
  int m_sensPin;
  int m_rawVal; //Storing as a float to save a cast later.
  float m_R;
  float m_tempDegC;
  
  

public:

  //TemperatureSensor constructor
  TemperatureSensor(const int analog_port);

  //Function:  init()
  //Description:  initilizes the PIN to be used for sensor.
  //Preconditions:  sensor pin has been set.
  //Postconditions:  The pinMode method is called and sets the sensor to input.
  void init();

  //Function:  getTemperature()
  //Description:  Performs check on sensor, updates read values. Needs to be called every cycle!
  //Postconditions:  Reads sensor, sets variables accordingly.
  float getTemp();

  //Function:  getPin()
  //Description:  Used for checking which PIN the sensor is on. 
  //Postconditions:  Returns PIN number for sensor. 
  int getPin();
};

#endif
