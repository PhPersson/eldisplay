#include "globals.h"


WiFiClientSecure client;


char api_url[45]   = "https://www.elprisetjustnu.se/api/v1/prices/";
bool isScreenOn = false;
float currentPrice = 0.0;
char  priceArea[4]  = "SE4";
float threshold     = 1.0f;
bool  addTax        = true;
bool  nightMode     = false;
