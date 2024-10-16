#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 


#include <user_config.h>
#include <certs.h>

#include "FileHandler.h"
#include "NetworkHandler.h"
#include "DisplayHandler.h"
#include "TimeHandler.h"

// Adds trsuted root-certs
BearSSL::X509List trustedRoots;

extern AsyncWebServer server;

void getElectricityPrices() {
  WiFiClientSecure client;
  HTTPClient http;
  client.setTrustAnchors(&trustedRoots);
  char url[100];
  snprintf(url, sizeof(url), "%s%s_%s.json", api_url, getCurrentDate(), electricityPriceArea);
  Serial.println(url);
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

    int currentHour = timeClient.getHours();
    int hoursDisplayed = 0;
    for (size_t i = 0; i < json.size(); i++) {
        String timeStart(json[i]["time_start"]);
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

          uint16_t textColor = (totalSekPerKwh > priceThreshold) ? ILI9341_RED : ILI9341_GREEN;

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
  
  initNetwork();
  setupMDNS();
  setHostname();
  setupWebServer(server);

  // Initialize LittleFS
  if (!initializeFileSystem()) {
    return;
  }

  trustedRoots.append(cert_ISRG_X1);
  trustedRoots.append(cert_ISRG_X2);

  initDisplay();
  initTime();

  Serial.println("Data från: elprisetjustnu.se");
  delay(500);
  if (checkValues(electricityPriceArea, sizeof(electricityPriceArea), priceThreshold, shouldAddTax)){
    getElectricityPrices();
  } else {
    displayNoValuesMessage();
  }

}

void loop() {

}