#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "globals.h"
#include "certs.h"
#include <HTTPClient.h>
#include <ApiHandler.h>
#include <DisplayHandler.h>
#include <AsyncTCP.h>


void getElectricityPrices() {
    HTTPClient http;
    char url[100];
    snprintf(url, sizeof(url), "%s%s_%s.json", api_url, getCurrentDate(), priceArea);
    client.setCACert(root_ca);
    http.begin(client, String(url));
    int httpCode = http.GET();
    if (httpCode > 0) {
        clearDisplay();
        String payload = http.getString();
        JsonDocument json;
        DeserializationError error = deserializeJson(json, payload);
        displayDeviceText();

        JsonArray data = json.as<JsonArray>();
        int currentHour = timeClient.getHours();
        int currentMinute = timeClient.getMinutes();
        int currentQuarter = (currentMinute / 15) * 15;
        int currentTotalMinutes = currentHour * 60 + currentQuarter;
        int timeDisplayed = 0;

        for (JsonObject obj : data) {
            String timeStart = obj["time_start"].as<String>();
            int startHour   = timeStart.substring(11, 13).toInt();
            int startMinute = timeStart.substring(14, 16).toInt();
            int slotTotalMinutes = startHour * 60 + startMinute;

            int diff = slotTotalMinutes - currentTotalMinutes;
            if (diff >= 0 && diff < 3 * 15) {

                float sekPerKwh = obj["SEK_per_kWh"];
                float totalSekPerKwh = sekPerKwh;

                if (loadBool("addTax", addTax)) {
                    totalSekPerKwh = sekPerKwh * 1.25 + 0.535;
                }
                totalSekPerKwh = round(totalSekPerKwh * 100.0) / 100.0;

                if (diff == 0) {
                    currentPrice = totalSekPerKwh;
                }

                uint16_t textColor = (totalSekPerKwh > loadFloat("threshold", threshold)) ? TFT_RED : TFT_GREEN;
                displayEnergyMessage(startHour, startMinute, totalSekPerKwh, timeDisplayed, textColor);
                timeDisplayed++;
                if (timeDisplayed >= 3) {
                    break;
                }
            }
        }

    } else {
        Serial.printf("HTTP request failed: %s\n", http.errorToString(httpCode).c_str());
        displayHttpErrorMessage(httpCode);
        delay(10000);
        ESP.restart();
    }

    http.end();
}