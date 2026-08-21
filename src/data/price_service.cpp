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

bool isValidPrice(float price)
{
  // Anpassa intervallet efter din API-enhet och applyTax().
  return isfinite(price) && price > -100.0f && price < 1000.0f;
}

bool parseT0(
  const char* t0,
  int& year,
  int& month,
  int& day,
  int& hour,
  int& minute,
  int& second,
  int& offsetMinutes
)
{
  if (t0 == nullptr || strlen(t0) < 19) {
    return false;
  }

  // Förväntat:
  // 2026-08-09T00:00:00+02:00
  if (t0[4] != '-' ||
      t0[7] != '-' ||
      t0[10] != 'T' ||
      t0[13] != ':' ||
      t0[16] != ':') {
    return false;
  }

  year =
    (t0[0] - '0') * 1000 +
    (t0[1] - '0') * 100 +
    (t0[2] - '0') * 10 +
    (t0[3] - '0');

  month =
    (t0[5] - '0') * 10 +
    (t0[6] - '0');

  day =
    (t0[8] - '0') * 10 +
    (t0[9] - '0');

  hour =
    (t0[11] - '0') * 10 +
    (t0[12] - '0');

  minute =
    (t0[14] - '0') * 10 +
    (t0[15] - '0');

  second =
    (t0[17] - '0') * 10 +
    (t0[18] - '0');

  offsetMinutes = 0;

  if (strlen(t0) >= 25) {
    const char sign = t0[19];

    if ((sign == '+' || sign == '-') &&
        t0[22] == ':') {
      const int offsetHours =
        (t0[20] - '0') * 10 +
        (t0[21] - '0');

      const int offsetMins =
        (t0[23] - '0') * 10 +
        (t0[24] - '0');

      offsetMinutes = offsetHours * 60 + offsetMins;

      if (sign == '-') {
        offsetMinutes = -offsetMinutes;
      }
    }
  }

  return year >= 2020 &&
         month >= 1 && month <= 12 &&
         day >= 1 && day <= 31 &&
         hour >= 0 && hour <= 23 &&
         minute >= 0 && minute <= 59 &&
         second >= 0 && second <= 59;
}

bool fetchUpcomingCurrentPrices()
{
  HTTPClient http;

  const String url = String("https://se.elpris.eu") + todayPath();

  Serial.printf("Fetching prices from: %s\n", url.c_str());

  client.stop();
  client.setInsecure();

  if (!http.begin(client, url)) {
    Serial.println("http.begin() failed");
    return false;
  }

  http.setTimeout(15000);

  const int httpCode = http.GET();

  if (httpCode <= 0) {
    Serial.printf(
      "HTTP error: %s\n",
      http.errorToString(httpCode).c_str()
    );
    http.end();
    return false;
  }

  if (httpCode != HTTP_CODE_OK) {
    Serial.printf("HTTP status: %d\n", httpCode);
    http.end();
    return false;
  }

  const String payload = http.getString();
  http.end();

  JsonDocument json;

  const DeserializationError error =
    deserializeJson(json, payload);

  if (error) {
    Serial.print("JSON error: ");
    Serial.println(error.c_str());
    return false;
  }

  const int stepSeconds = json["s"] | 0;

  if (stepSeconds <= 0 || stepSeconds > 3600) {
    Serial.printf("Invalid step size: %d\n", stepSeconds);
    return false;
  }

  JsonArray data = json["p"].as<JsonArray>();

  if (data.isNull() || data.size() == 0) {
    Serial.println("No price data");
    return false;
  }

  const char* startTime = json["t0"] | "";

  int startYear;
  int startMonth;
  int startDay;
  int startHour;
  int startMinute;
  int startSecond;
  int startOffsetMinutes;

  if (!parseT0(
        startTime,
        startYear,
        startMonth,
        startDay,
        startHour,
        startMinute,
        startSecond,
        startOffsetMinutes
      )) {
    Serial.printf("Invalid t0: %s\n", startTime);
    return false;
  }

  struct tm nowInfo{};

  if (!getLocalTime(&nowInfo, 1000)) {
    Serial.println("No time loaded");
    return false;
  }

  Serial.printf(
    "t0=%s, local now=%04d-%02d-%02d %02d:%02d:%02d\n",
    startTime,
    nowInfo.tm_year + 1900,
    nowInfo.tm_mon + 1,
    nowInfo.tm_mday,
    nowInfo.tm_hour,
    nowInfo.tm_min,
    nowInfo.tm_sec
  );


  const int nowSeconds =
    nowInfo.tm_hour * 3600 +
    nowInfo.tm_min * 60 +
    nowInfo.tm_sec;

  const int startSeconds =
    startHour * 3600 +
    startMinute * 60 +
    startSecond;

  const int elapsedSeconds =
    nowSeconds - startSeconds;

  if (elapsedSeconds < 0) {
    Serial.println("Current time is before t0");
    return false;
  }

  const int currentIndex =
    elapsedSeconds / stepSeconds;

  if (currentIndex < 0 ||
      currentIndex >= static_cast<int>(data.size())) {
    Serial.printf(
      "Current index out of range: %d / %u\n",
      currentIndex,
      static_cast<unsigned>(data.size())
    );
    return false;
  }

  float newCurrentPrice =
    applyTax(data[currentIndex].as<float>());

  float newUpcomingPrice1 = NAN;
  float newUpcomingPrice2 = NAN;

  if (currentIndex + 1 < static_cast<int>(data.size())) {
    newUpcomingPrice1 =
      applyTax(data[currentIndex + 1].as<float>());
  }

  if (currentIndex + 2 < static_cast<int>(data.size())) {
    newUpcomingPrice2 =
      applyTax(data[currentIndex + 2].as<float>());
  }

  if (!isValidPrice(newCurrentPrice)) {
    Serial.printf(
      "Invalid current price at index %d: %.3f\n",
      currentIndex,
      newCurrentPrice
    );
    return false;
  }

  if (!isnan(newUpcomingPrice1) &&
      !isValidPrice(newUpcomingPrice1)) {
    Serial.printf(
      "Invalid upcoming price 1: %.3f\n",
      newUpcomingPrice1
    );
    return false;
  }

  if (!isnan(newUpcomingPrice2) &&
      !isValidPrice(newUpcomingPrice2)) {
    Serial.printf(
      "Invalid upcoming price 2: %.3f\n",
      newUpcomingPrice2
    );
    return false;
  }

  Serial.printf(
    "Using index %d: current=%.3f, next=%.3f, next2=%.3f\n",
    currentIndex,
    newCurrentPrice,
    newUpcomingPrice1,
    newUpcomingPrice2
  );

  currentPrice = newCurrentPrice;
  upcomingPrice1 = newUpcomingPrice1;
  upcomingPrice2 = newUpcomingPrice2;

  return true;
}