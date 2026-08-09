#include "app_state.h"

String priceArea = "SE4";
bool addTax = false;
float threshold = 1.0f;
float currentPrice = 0.0f;
float upcomingPrice1 = 0.0f;
float upcomingPrice2 = 0.0f;
volatile bool restartRequested = false;