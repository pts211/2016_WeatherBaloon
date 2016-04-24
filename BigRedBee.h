#ifndef BIGREDBEE_H
#define BIGREDBEE_H

#include <Arduino.h>
#include <TinyGPS++.h>

class BigRedBee
{
private:
  TinyGPSPlus gps;
  HardwareSerial * m_serial;
  int m_baud;

  bool m_unreadMessage;
  bool m_readInProgress;
  String m_gpsString;
  String m_tempStr;

public:

  //BigRedBee constructor
  BigRedBee(HardwareSerial * s, const int baud = 9600)
  {
    m_serial = s;
    m_baud = baud;

    m_unreadMessage = false;
    m_readInProgress = false;
    m_gpsString = "";
  }

  void init()
  {
    m_serial->begin(m_baud);
  }

  bool poll()
  {
    while (m_serial->available() > 0) {
      gps.encode(m_serial->read());
    }
  }

  String printColHeadings()
  {
    return "Time, Latitude, Longitude";
  }

  String print()
  {
    return printTime() + ", " + printLocation();
    //return "test";
  }

  String printLocation()
  {
    String locStr = "";
    if (gps.location.isValid())
    {
      locStr += String(gps.location.lat());
      locStr += ", ";

      locStr += String(gps.location.lng());
      locStr += ", ";
    }
    else
    {
      locStr = "INVALID";
    }
  }
  
  String printTime()
  {
    String timeStr = "";
    
    if (gps.time.isValid())
    {
      if (gps.time.hour() < 10) timeStr += "0";
      timeStr += gps.time.hour();
      timeStr += ":";
      if (gps.time.minute() < 10) timeStr += "0";
      timeStr += gps.time.minute();
      timeStr += ":";
      if (gps.time.second() < 10) timeStr += "0";
      timeStr += gps.time.second();
      timeStr += ":";
      if (gps.time.centisecond() < 10) timeStr += "0";
      timeStr += gps.time.centisecond();
    }
    else
    {
      Serial.print(F("INVALID"));
    }
  }
  
  void displayInfo()
  {
    Serial.print(F("Location: ")); 
    if (gps.location.isValid())
    {
      Serial.print(gps.location.lat(), 6);
      Serial.print(F(","));
      Serial.print(gps.location.lng(), 6);
    }
    else
    {
      Serial.print(F("INVALID"));
    }
  
    Serial.print(F("  Date/Time: "));
    if (gps.date.isValid())
    {
      Serial.print(gps.date.month());
      Serial.print(F("/"));
      Serial.print(gps.date.day());
      Serial.print(F("/"));
      Serial.print(gps.date.year());
    }
    else
    {
      Serial.print(F("INVALID"));
    }
  
    Serial.print(F(" "));
    if (gps.time.isValid())
    {
      if (gps.time.hour() < 10) Serial.print(F("0"));
      Serial.print(gps.time.hour());
      Serial.print(F(":"));
      if (gps.time.minute() < 10) Serial.print(F("0"));
      Serial.print(gps.time.minute());
      Serial.print(F(":"));
      if (gps.time.second() < 10) Serial.print(F("0"));
      Serial.print(gps.time.second());
      Serial.print(F("."));
      if (gps.time.centisecond() < 10) Serial.print(F("0"));
      Serial.print(gps.time.centisecond());
    }
    else
    {
      Serial.print(F("INVALID"));
    }
  
    Serial.println();
  }
};

#endif
