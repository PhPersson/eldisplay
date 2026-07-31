#include <Arduino.h>
#include "FileHandler.h"
#include "NetworkHandler.h"
#include "DisplayHandler.h"
#include "TimeHandler.h"
#include "ApiHandler.h"
#include "globals.h"

extern AsyncWebServer server;
unsigned long lastMillis = 0;
bool apiFetchedThisHour = false;


void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  initDisplay();
  delay(500);
  initNetwork();
  delay(500);
  initializePreferences();
  MDNS.begin("eldisplay");
  setupWebServer(server);

  initTime();

  Serial.println("Data från: elprisetjustnu.se");
  delay(500);
  if(!checkValues(priceArea,threshold,nightMode)){
    displaySetupMessage(getIP()); 
  } else{
    getElectricityPrices();
  }
  displayMDNS(getIP());
}
const char* ntpServer = "pool.ntp.org";
const char* tzSweden  = "CET-1CEST,M3.5.0/02,M10.5.0/03";
struct tm timeinfo;
void initTime() {
    configTzTime(tzSweden, ntpServer);


    while (!getLocalTime(&timeinfo)) {
        delay(500);
    }

}

void loop() {
  unsigned long currentMillis = millis();
  int currentMinute = timeinfo.tm_min;

  if ((currentMinute % 15 == 0) && !apiFetchedThisHour) {
    getElectricityPrices();
    displayMDNS(getIP());
    apiFetchedThisHour = true;
  }

  if (currentMinute % 15 != 0) {
  apiFetchedThisHour = false;
  }

    if (nightMode) {
      int currentHour = timeinfo.tm_hour;
      if (currentHour >= 23 || currentHour < 6) {
        turnOffDisplay();
      } else {
        turnOnDisplay();
      }
    }
  loopOTA();
}
