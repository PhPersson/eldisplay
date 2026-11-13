#pragma once
#include <Arduino.h>

extern String priceArea;
extern bool showOnlyCurrentPrice;
extern bool addTax;
extern float threshold;
extern float currentPrice;
extern float upcomingPrice1;
extern float upcomingPrice2;

extern volatile bool restartRequested;