#ifndef BIGREDBEE_H
#define BIGREDBEE_H

#include <Arduino.h>
#include <TinyGPS++.h>

#define FLOAT_PRECISION 6 //The number of digits to print for the lon/lat coordinates

class BigRedBee
{
private:
  TinyGPSPlus gps;
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

  bool poll()
  {
    while(m_serial->available() > 0) {
      gps.encode(m_serial->read());
    }
  }
  
  void printColHeadings(HardwareSerial * s, const bool includeDelimiter = false)
  {
    s->print(F("Time, Latitude, Longitude, Altitude (m)"));
    if(includeDelimiter){
      s->print(F(", "));
    }
  }

  void print(HardwareSerial * s, const bool includeDelimiter = false)
  {
    
    /* ********** TIME ********** */
    if (gps.time.isValid())
    {
      char t = gps.time.hour();
      if (t < 10){
        s->print(F("0"));
      }
      s->print(t);
      s->print(F(":"));
      
      t = gps.time.minute();
      if (t < 10){
        s->print(F("0"));
      }
      s->print(t);
      s->print(F(":"));
      
      t = gps.time.second();
      if (t < 10){
        s->print(F("0"));
      }
      s->print(t);
      s->print(F(":"));
      
      t = gps.time.centisecond();
      if (t < 10){
        s->print(F("0"));
      }
      s->print(t);
    }else{
      s->print(F("INVALID"));
    }
    s->print(F(", "));
    
    /* ********** LOCATION ********** */
    if (gps.location.isValid())
    {
      s->print(gps.location.lat(), FLOAT_PRECISION);
      s->print(F(", "));
      
      s->print(gps.location.lng(), FLOAT_PRECISION);
      s->print(F(", "));
      
    }else{
      s->print(F("INVALID, INVALID, "));
    }
    
    /* ********** ALTITUDE ********** */
    if(gps.altitude.isValid()){
      s->print(gps.altitude.meters());
    }else{
      s->print(F("INVALID"));
    }
    
    if(includeDelimiter){
      s->print(F(", "));
    }
  }
};

#endif
