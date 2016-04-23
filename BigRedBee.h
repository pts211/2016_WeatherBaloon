#ifndef BIGREDBEE_H
#define BIGREDBEE_H

#include <Arduino.h>

class BigRedBee
{
private:
  HardwareSerial * m_serial;   
  int m_baud;

public:

  //BigRedBee constructor
  BigRedBee(HardwareSerial * s, const int baud = 9600)
  {
    m_serial = s;
    m_baud = baud;
  }

  void init()
  {
    m_serial->begin(m_baud);
  }

  void read()
  {
    
  }
  
  String print()
  {
    return "BigRedBee";
  }

  String printWithLabels()
  {
    return "BigRedBee (With Labels!)";
  }
};

#endif
