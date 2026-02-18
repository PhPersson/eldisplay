#ifndef GLOBALS_H
#define GLOBALS_H

#include <WiFiClientSecure.h>

extern WiFiClientSecure client;


extern float threshold;
extern bool addTax;
extern bool nightMode;
extern bool isScreenOn;    
extern char api_url[45];
extern char priceArea[4];
extern float currentPrice;
#endif