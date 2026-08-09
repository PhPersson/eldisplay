#pragma once

extern float currentPrice;
extern float upcomingPrice1;
extern float upcomingPrice2;

float applyTax(float price);
bool fetchCurrentPrice();
bool fetchUpcomingCurrentPrices();