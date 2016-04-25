#ifndef OPENLOGGER_H
#define OPENLOGGER_H

#include <Arduino.h>

class OpenLogger
{
private:
  HardwareSerial * m_serial;   
  int m_baud;

public:

  //OpenLogger constructor
  OpenLogger(HardwareSerial * s, const int baud = 9600)
  {
    m_serial = s;
    m_baud = baud;
  }

  void init()
  {
    m_serial->begin(m_baud);
  }
  
  HardwareSerial* getSerial()
  {
    return m_serial;
  }

  void log(const String txt)
  {
    m_serial->print(txt);
  }
  
  void logln(const String txt)
  {
    m_serial->println(txt);
  }
  
  String print()
  {
    return "OpenLogger";
  }

  String printWithLabels()
  {
    return "OpenLogger (With Labels!)";
  }
};

#endif
