#include <Arduino.h>
#include "FileHandler.h"
#include "NetworkHandler.h"
#include "DisplayHandler.h"
#include "TimeHandler.h"
#include "Utils.h"
#include "ApiHandler.h"

extern AsyncWebServer server;
unsigned long lastMillis = 0;
bool apiFetchedThisHour = false;


void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  disableLED();
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
    displaySetupMessage(); 
    return;
  } else{
    getElectricityPrices();
  }
}



void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillis >= 60000 ) {
    lastMillis = currentMillis;

    timeClient.update();
    int currentMinute = timeClient.getMinutes();

    if (currentMinute == 5 && !apiFetchedThisHour && !nightMode) {
      getElectricityPrices();
      apiFetchedThisHour = true;
    }

    if (currentMinute != 5) {
      apiFetchedThisHour = false;
    }

    if (nightMode) {
      int currentHour = timeClient.getHours();
      if (currentHour >= 23 || currentHour < 6) {
        turnOffDisplay();
      } else {
        turnOnDisplay();
      }
    }
    
  }
  loopOTA();
}