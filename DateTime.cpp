
#include "DateTime.h"


#define NTP_SERVER "de.pool.ntp.org"
//#define TZ_INFO "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00"
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03" 


void DateTime::begin()
{

  struct tm local;
     configTzTime(MY_TZ, NTP_SERVER); // ESP32 Systemzeit mit NTP Synchronisieren
     getLocalTime(&local, 10000);  

   this->update();  
     
/*   int tz = 1;

  this->ntp = new NTPClient(udp, tz * 3600);
  setTime(ntp->getEpochTime());
  
  ntp->begin();
  ntp->forceUpdate(); */
}

void DateTime::update()
{
  //ntp->update();
  struct tm local;
  getLocalTime(&local, 1000); 
  last_hour = local.tm_hour;
  last_min  = local.tm_min;
  last_sec = local.tm_sec;
    uhrzeit[0] = last_hour / 10;
    uhrzeit[1] = last_hour % 10;
    uhrzeit[2] = last_min / 10;
    uhrzeit[3] = last_min % 10;
    uhrzeit[4] = last_sec / 10;
    uhrzeit[5] = last_sec % 10;
}

String DateTime::getFormattedTime()
{
  //return ntp->getFormattedTime();
  return "";
}

char* DateTime::getHour(const char *format)
{
  static char buffer[3] = {'\0'};
  //snprintf(buffer, sizeof(buffer), format, ntp->getHours());
  snprintf(buffer, sizeof(buffer), format, last_hour);
  return buffer;
}

char* DateTime::getMinute(const char *format)
{
  static char buffer[3] = {'\0'};
  //snprintf(buffer, sizeof(buffer), format, ntp->getMinutes());
  snprintf(buffer, sizeof(buffer), format, last_min);
  return buffer;
}

int DateTime::getHour() {
  return last_hour;
}

int DateTime::getMinute() {
  return last_min;
}

int DateTime::getSecond() {
  return last_sec;
}
