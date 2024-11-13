#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 

#include <HTTPClient.h>

#include <user_config.h>
#include <certs.h>

#include "FileHandler.h"
#include "NetworkHandler.h"
#include "DisplayHandler.h"
#include "TimeHandler.h"


WiFiClientSecure client;


extern AsyncWebServer server;
unsigned long lastMillis = 0;
bool apiFetchedThisHour = false;

void getElectricityPrices() {

  HTTPClient http;

  

  char url[100];
  snprintf(url, sizeof(url), "%s%s_%s.json", api_url, getCurrentDate(), electricityPriceArea);
  delay(1000);
  http.begin(client,url);
  int httpCode = http.GET();


  if (httpCode > 0) {
    String payload = http.getString();
    JsonDocument json;
    DeserializationError error = deserializeJson(json, payload);

    if (error) {
      displayJsonError(error.c_str());
    }

    displayDeviceText();
    serializeJson(json, Serial);
    int currentHour = timeClient.getHours();
    int hoursDisplayed = 0;
    for (size_t i = 0; i < json.size(); i++) {
        String timeStart = json[i]["time_start"].as<String>();

        int startOfHour = timeStart.substring(11, 13).toInt(); 

        if (startOfHour == currentHour || startOfHour == (currentHour + 1) % 24 || startOfHour == (currentHour + 2) % 24) {
          float sekPerKwh = json[i]["SEK_per_kWh"];
          float totalSekPerKwh = 0;

          if (shouldAddTax) {
              totalSekPerKwh = sekPerKwh * 1.25; // 25% tax
          } else {
              totalSekPerKwh = sekPerKwh;
          }
          totalSekPerKwh = round(totalSekPerKwh * 100.0) / 100.0;
          
          uint16_t textColor = (totalSekPerKwh > priceThreshold) ? TFT_RED : TFT_GREEN;

          displayEnergyMessage(startOfHour, totalSekPerKwh, hoursDisplayed, textColor);

          hoursDisplayed++;

          if (hoursDisplayed >= 3) {
              break;
          }
        }
    }

  } else {
    displayHttpErrorMessage(httpCode);
  }

  http.end();
  displayMDNS();
}


void setup() {
  Serial.begin(115200);
  initDisplay();
  delay(500);
  initNetwork();
  delay(500);
  initializePreferences();
  setupWebServer(server);
  client.setCACert(cert_ISRG_X1);
  delay(500);
  initTime();

  Serial.println("Data från: elprisetjustnu.se");
  delay(500);
  getElectricityPrices();
  // if (checkValues(electricityPriceArea, sizeof(electricityPriceArea), priceThreshold, shouldAddTax)){
  //   getElectricityPrices();
  // } else {
  //   displayNoValuesMessage();
  // }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillis >= 60000) {
    lastMillis = currentMillis;

    timeClient.update();
    int currentMinute = timeClient.getMinutes();

    if (currentMinute == 5 && !apiFetchedThisHour) {
      getElectricityPrices(); 
      apiFetchedThisHour = true;   
    }

    if (currentMinute != 5) {
      apiFetchedThisHour = false;
    }
  }
  loopOTA();
}