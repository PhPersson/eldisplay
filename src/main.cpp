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
  #if defined(BOARD_ESP32_CYD)
    if (fetchUpcomingCurrentPrices()) {
      drawUpcomingPrices(currentPrice, upcomingPrice1, upcomingPrice2, threshold);
    } else {
      drawCenteredMessage("Error");
      delay(10000);
      ESP.restart();
    }
  #else
    if (fetchCurrentPrice()) {
      drawCenteredPrice(currentPrice, threshold);
    } else {
      drawCenteredMessage("Error");
      delay(10000);
      ESP.restart();
    }
  #endif
}

constexpr unsigned long FETCH_INTERVAL_MS = 5UL * 60UL * 1000UL;
constexpr unsigned long ERROR_RESTART_DELAY_MS = 10UL * 1000UL;

bool restartPending = false;
unsigned long restartAt = 0;

void requestRestart(unsigned long delayMs = 0)
{
  restartPending = true;
  restartAt = millis() + delayMs;
}

void handleRestart()
{
  if (restartPending &&
      static_cast<long>(millis() - restartAt) >= 0) {
    ESP.restart();
  }
}

void handleFetchError()
{
  drawCenteredMessage("Error");
  requestRestart(ERROR_RESTART_DELAY_MS);
}

void fetchAndDrawPrices()
{
#if defined(BOARD_ESP32_CYD)
  if (fetchUpcomingCurrentPrices()) {
    drawUpcomingPrices(
      currentPrice,
      upcomingPrice1,
      upcomingPrice2,
      threshold
    );
  } else {
    handleFetchError();
  }
#else
  if (fetchCurrentPrice()) {
    drawCenteredPrice(currentPrice, threshold);
  } else {
    handleFetchError();
  }
#endif
}

void loop()
{
  if (restartRequested) {
    requestRestart(500);
  }

  handleRestart();

  if (!restartPending) {
    const unsigned long now = millis();

    if (now - lastFetch >= FETCH_INTERVAL_MS) {
      fetchAndDrawPrices();
      lastFetch = now;
    }
  }

  delay(10);
}