#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

#include <NTPClient.h>
#include <WiFiUdp.h>

extern WiFiUDP udp;
extern NTPClient timeClient;
const char* getCurrentDate();
void initTime();

#endif