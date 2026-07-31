#include <Arduino.h>

#include "webui.h"
#include "display_manager.h"
#include "time_manager.h"
#include "app_state.h"
#include "wifi_manager.h"
#include "settings.h"
#include "price_service.h"

unsigned long lastFetch = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  setupDisplay();
  drawCenteredMessage("Starting up");
  loadSettings();
  delay(2500);
  connectWifi();
  setupTime();
  setupWeb();

  if (fetchCurrentPrice()) {
    drawCenteredPrice(currentPrice);
  } else {
    drawCenteredMessage("Error");
    delay(10000);
    ESP.restart();
  }

  lastFetch = millis();
}

void loop() {
  if (restartRequested) {
    delay(500);
    ESP.restart();
  }
  if (millis() - lastFetch > 5UL * 60UL * 1000UL) {
    if (fetchCurrentPrice()) {
      drawCenteredPrice(currentPrice);
    } else {
      drawCenteredMessage("Error");
    }
    lastFetch = millis();
  }

  delay(250);
}