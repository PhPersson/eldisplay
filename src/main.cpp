#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <user_config.h>
#include <certs.h>

#include "FileHandler.h"
#include "NetworkHandler.h"
#include "DisplayHandler.h"

// Adds trsuted root-certs
BearSSL::X509List trustedRoots;

extern AsyncWebServer server;
// NTP setup
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", 7200); // UTC+1

String getCurrentDate(){
  time_t rawTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime(&rawTime);

  char dateStr[12];
  strftime(dateStr, sizeof(dateStr), "%Y/%m-%d", ptm);
  return String(dateStr);
}

void getElectricityPrices() {
  WiFiClientSecure client;
  HTTPClient http;
  client.setTrustAnchors(&trustedRoots);
  String url = api_url + getCurrentDate() + "_" + electricityPriceArea +".json"; // Dynamiclly use todays date using concatenation
  Serial.println(url);
  delay(1000);
  http.begin(client,url);
  int httpCode = http.GET(); // Make request to the api


  if (httpCode > 0) {
    String payload = http.getString();
    JsonDocument json;
    DeserializationError error = deserializeJson(json, payload);

    if (error) { // If there's any error deseralize the json in the response
      Serial.print("Failed to parse JSON: ");
      Serial.println(error.c_str());
      tft.fillScreen(ILI9341_BLACK); // Clears the screen before displaying new text
      tft.setCursor(10, 10);
      tft.setTextColor(ILI9341_RED);
      tft.println("Error from API");
      tft.setCursor(10, 40);
      tft.println(error.c_str());
      return;
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

  }

  else {
  displayHttpErrorMessage(httpCode);
  }
  http.end();
  displayMDNS();

}


void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  
  initNetwork();
  setupMDNS();
  setHostname();
  setupWebServer(server);

  // Initialize LittleFS
  if (!initializeFileSystem()) {
    return;
  }

  timeClient.begin();
  timeClient.update(); 

  trustedRoots.append(cert_ISRG_X1);
  trustedRoots.append(cert_ISRG_X2);

  initDisplay();

  if (checkValues(electricityPriceArea, sizeof(electricityPriceArea), priceThreshold, shouldAddTax)){
    getElectricityPrices();
  } else {
    displayNoValuesMessage();
  }

}

void loop() {
  MDNS.update();
}