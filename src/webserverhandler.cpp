#include "WebServerHandler.h"
#include "user_config.h"
#include "FileHandler.h"


// Define parameter names
const char* PARAM_AREA = "area";
const char* PARAM_THRESHOLD = "threshold";
const char* PARAM_TAX = "tax";
const char* PARAM_ELOVERFORING = "eloverforingCheckbox";
const char* PARAM_TRANSFERFEE = "transferFee";

void setupWebServer(AsyncWebServer &server) {
    // Route for root index.html
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });

    // Route for handling not found (404) errors
    server.onNotFound(notFound);

    server.on("/update", HTTP_POST, [] (AsyncWebServerRequest *request) {
        // Temporary variables to hold form values as strings
        String area = "";
        String threshold = "";
        String tax = "unchecked";
        String eloverforing = "unchecked";
        String transferFeeStr = "";

        // Get the 'area' value from the form
        if (request->hasParam(PARAM_AREA, true)) {
            area = request->getParam(PARAM_AREA, true)->value();
            strncpy(electricityPriceArea, area.c_str(), sizeof(electricityPriceArea) - 1); // Copy to char[]
            electricityPriceArea[sizeof(electricityPriceArea) - 1] = '\0';  // Ensure null-termination

            // Save updated electricity price area to LittleFS
            saveCharToLittleFS("/electricityPriceArea.txt", electricityPriceArea);
        }

        // Get the 'threshold' value from the form
        if (request->hasParam(PARAM_THRESHOLD, true)) {
            threshold = request->getParam(PARAM_THRESHOLD, true)->value();
            priceThreshold = threshold.toFloat();  // Convert to float

            // Save updated price threshold to LittleFS
            saveFloatToLittleFS("/priceThreshold.txt", priceThreshold);
        }

        // Get the 'tax' checkbox value from the form (checkboxes are optional)
        if (request->hasParam(PARAM_TAX, true)) {
            shouldAddTax = true;  // Checkbox is checked
        } else {
            shouldAddTax = false; // Checkbox is unchecked
        }

        // Save updated tax inclusion setting to LittleFS
        saveBoolToLittleFS("/shouldAddTax.txt", shouldAddTax);

        delay(1000);
        ESP.restart();
    });

    // Start the server
    server.begin();
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
