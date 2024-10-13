#pragma once
#include <WString.h>


char* electricityPriceArea = ""; // Any of SE1, SE2, SE3 or SE4
String api_url = ""; // API-url to fetch the price
float priceThreshold = 0.5; // The threshold when price should be consider high
bool shouldAddTax = true; // false if not include tax, only tariff