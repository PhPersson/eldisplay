#include "price_service.h"
#include "app_state.h"
#include "time_manager.h"
#include "display_manager.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

static WiFiClientSecure client;

float currentPrice = 0.0f;

float applyTax(float price) {
  if (applyTax) {
    price = price * 1.25f + 0.535f;
  }
  return roundf(price * 100.0f) / 100.0f;
}


bool fetchCurrentPrice() {
  HTTPClient http;
  String url = String("https://se.elpris.eu") + todayPath();
  client.stop();
  client.setInsecure();

  if (!http.begin(client, url)) {
    Serial.println("http.begin() failed");
    return false;
  }

  int httpCode = http.GET();

  if (httpCode <= 0) {
    drawCenteredMessage("HTTP error: " + http.errorToString(httpCode));
    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  JsonDocument json;
  DeserializationError error = deserializeJson(json, payload);
  if (error) {
    return false;
  }

  int stepSeconds = json["s"] | 900;
  String t0 = String((const char*)json["t0"]);
  JsonArray data = json["p"].as<JsonArray>();

  if (data.isNull() || data.size() == 0) {
    drawCenteredMessage("No price data");
    return false;
  }

  struct tm nowInfo;
  if (!getLocalTime(&nowInfo, 1000)) {
    drawCenteredMessage("No time loaded");
    return false;
  }

  int currentIndex = nowInfo.tm_hour * 4 + (nowInfo.tm_min / 15);

  if (currentIndex < 0 || currentIndex >= data.size()) {
    Serial.println("Index out of range");
    return false;
  }

  currentPrice = applyTax(data[currentIndex].as<float>());
  return true;
}