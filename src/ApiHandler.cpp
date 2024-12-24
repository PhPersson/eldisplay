#include <ApiHandler.h>

WiFiClientSecure client;

void getElectricityPrices() {

    HTTPClient http;
    char url[100];
    client.setCACert(cert_ISRG_X1);
    snprintf(url, sizeof(url), "%s%s_%s.json", api_url, getCurrentDate(), priceArea);
    delay(1000);

    http.begin(client, url);
    int httpCode = http.GET();

    if (httpCode > 0) {
        clearDisplay();
        String payload = http.getString();
        JsonDocument json;
        DeserializationError error = deserializeJson(json, payload);
        displayDeviceText();

        JsonArray data = json.as<JsonArray>();
        int currentHour = timeClient.getHours();
        int hoursDisplayed = 0;
        for (JsonObject obj : data) {
            String timeStart = obj["time_start"].as<String>();
            int startOfHour = timeStart.substring(11, 13).toInt();

            if (startOfHour == currentHour || startOfHour == (currentHour + 1) % 24 || startOfHour == (currentHour + 2) % 24) {

                float sekPerKwh = obj["SEK_per_kWh"];
                float totalSekPerKwh = sekPerKwh;

                if (loadBool("addTax", addTax)) {
                    totalSekPerKwh = sekPerKwh * 1.25 + 0.535;
                } else {
                    totalSekPerKwh = sekPerKwh;
                }

                totalSekPerKwh = round(totalSekPerKwh * 100.0) / 100.0; 

                uint16_t textColor = (totalSekPerKwh > loadFloat("threshold", threshold)) ? TFT_RED : TFT_GREEN;

                displayEnergyMessage(startOfHour, totalSekPerKwh, hoursDisplayed, textColor);
                hoursDisplayed++;

                if (hoursDisplayed >= 3) {
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