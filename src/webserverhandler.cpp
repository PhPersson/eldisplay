#include "WebServerHandler.h"
#include "user_config.h"
#include "FileHandler.h"


const char* PARAM_AREA = "area";
const char* PARAM_THRESHOLD = "threshold";
const char* PARAM_TAX = "tax";

void setupWebServer(AsyncWebServer &server) {

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });

    server.onNotFound(notFound);

    server.on("/update", HTTP_POST, [] (AsyncWebServerRequest *request) {

        if (request->hasParam(PARAM_AREA, true)) {
            
            String area = request->getParam(PARAM_AREA, true)->value();
            strncpy(electricityPriceArea, area.c_str(), sizeof(electricityPriceArea) - 1);
            electricityPriceArea[sizeof(electricityPriceArea) - 1] = '\0';  // Ensure null-termination
            
            saveCharToLittleFS("/electricityPriceArea.txt", electricityPriceArea);
        }


        if (request->hasParam(PARAM_THRESHOLD, true)) {
            priceThreshold = request->getParam(PARAM_THRESHOLD, true)->value().toFloat();

            saveFloatToLittleFS("/priceThreshold.txt", priceThreshold);
        }

        if (request->hasParam(PARAM_TAX, true)) {
            shouldAddTax = true; 
        } else {
            shouldAddTax = false;
        }

        saveBoolToLittleFS("/shouldAddTax.txt", shouldAddTax);

        delay(1000);
        ESP.restart();
    });

    server.begin();
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
