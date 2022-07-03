#ifndef DateTimeCf_h
#define DateTimeCf_h

#include <NTPClient.h>
#include <TimeLib.h>
#include <WiFi.h>

extern byte uhrzeit[];

class DateTime
{
  private:    
    WiFiUDP udp;
    NTPClient* ntp;

  public:
  int16_t last_hour = -1;
  int16_t last_min  = -1;
  int16_t last_sec  = -1;
  
    void begin();
    void update();
    String getFormattedTime();

    char* getHour(const char *format);
    char* getMinute(const char *format);
    
    int getHour();
    int getMinute();
    int getSecond();
};
#endif
