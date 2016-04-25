#ifndef GEIGERCOUNTER_H
#define GEIGERCOUNTER_H

#include <Arduino.h>
class GeigerCounter
{
private:
  
  const int BUFFLENGTH = 80;
  
  HardwareSerial * m_serial;
  int m_baud;

  String m_commandBuffer;
  String m_completeStr;

public:
  
  //GeigerCounter constructor
  GeigerCounter(HardwareSerial * s, const int baud = 9600)
  {
    m_commandBuffer.reserve(BUFFLENGTH);
    m_completeStr.reserve(BUFFLENGTH);
    
    m_serial = s;
    m_baud = baud;

    m_commandBuffer = "";
    m_completeStr = "CPS, 0, CPM, 0, uSv/hr, 0.00, SLOW";
  }

  void init()
  {
    m_serial->begin(m_baud);
  }

  bool poll()
  {
    //Serial.println("********** PRINTING OUT FROM THE POLL METHOD! **********");
    int buffCntr = 0;
    boolean isListen = true;
    while(m_serial->available() && buffCntr<BUFFLENGTH && isListen){
      char input = m_serial->read();
      if(input == '\n'){
        isListen = false;
        m_completeStr = m_commandBuffer;
        m_commandBuffer = "";
      }
      else{
        m_commandBuffer.concat(input);
        buffCntr++;
      }
    }
  }
  
  void printColHeadings(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(F("CPS, CPS_C, CPM, CPM_C, uSvHr, uSvHr_c, Speed"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
  
  void print(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(m_completeStr);
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
};

#endif
