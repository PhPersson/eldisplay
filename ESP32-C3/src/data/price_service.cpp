#include "price_service.h"
#include "app_state.h"
#include "time_manager.h"
#include "display_manager.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

static WiFiClientSecure client;



float applyTax(float price) {
  if (addTax) {
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


bool fetchUpcomingCurrentPrices() {
    HTTPClient http;

    String url = String("https://se.elpris.eu") + todayPath();
    Serial.printf("Fetching current price from: %s\n", url.c_str());
    client.stop();
    client.setInsecure();

    if (!http.begin(client, url)) {
        Serial.println("http.begin() failed");
        return false;
    }

    int httpCode = http.GET();

    if (httpCode <= 0) {
        Serial.println("HTTP error: " + http.errorToString(httpCode));
        http.end();
        return false;
    }

    if (httpCode != HTTP_CODE_OK) {
        Serial.printf("HTTP status: %d\n", httpCode);
        http.end();
        return false;
    }

    String payload = http.getString();
    http.end();

    JsonDocument json;

    DeserializationError error = deserializeJson(json, payload);

    if (error) {
        Serial.print("JSON error: ");
        Serial.println(error.c_str());
        return false;
    }

    int stepSeconds = json["s"] | 900;

    JsonArray data = json["p"].as<JsonArray>();

    if (data.isNull() || data.size() == 0) {
        Serial.println("No price data");
        return false;
    }

    struct tm nowInfo;

    if (!getLocalTime(&nowInfo, 1000)) {
        Serial.println("No time loaded");
        return false;
    }

    // 15-minute index:
    // 00:00 = 0
    // 00:15 = 1
    // 00:30 = 2
    // 00:45 = 3
    // ...
    const char* startTime = json["t0"] | "";

if (strlen(startTime) < 16) {
    Serial.println("Invalid t0");
    return false;
}

// t0 exempel: 2026-08-09T00:00:00+02:00
int startHour =
    (startTime[11] - '0') * 10 +
    (startTime[12] - '0');

int startMinute =
    (startTime[14] - '0') * 10 +
    (startTime[15] - '0');

int nowSeconds =
    nowInfo.tm_hour * 3600 +
    nowInfo.tm_min * 60 +
    nowInfo.tm_sec;

int startSeconds =
    startHour * 3600 +
    startMinute * 60;

int elapsedSeconds = nowSeconds - startSeconds;

if (elapsedSeconds < 0) {
    Serial.println("Time is before first price");
    return false;
}

int currentIndex = elapsedSeconds / stepSeconds;

if (currentIndex < 0 ||
    currentIndex >= static_cast<int>(data.size())) {
    Serial.println("Current index out of range");
    return false;
}

  currentPrice =
      applyTax(data[currentIndex].as<float>());

  if (currentIndex + 1 < data.size()) {
      upcomingPrice1 =
          applyTax(data[currentIndex + 1].as<float>());
  } else {
      upcomingPrice1 = NAN;
  }

  if (currentIndex + 2 < data.size()) {
      upcomingPrice2 =
          applyTax(data[currentIndex + 2].as<float>());
  } else {
      upcomingPrice2 = NAN;
  }
  return true;
}