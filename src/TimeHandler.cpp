#include "TimeHandler.h"


WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", 3600); // UTC+1

const char* getCurrentDate(){
  time_t rawTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime(&rawTime);

  static char dateStr[12];
  strftime(dateStr, sizeof(dateStr), "%Y/%m-%d", ptm);
  return dateStr;
}

void initTime(){
  timeClient.begin();
  timeClient.update(); 
}