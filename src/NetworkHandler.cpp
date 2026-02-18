#include "globals.h"
#include "NetworkHandler.h"
#include "DisplayHandler.h"
#include "index_html.h"

AsyncWebServer server(80);
WiFiManager wifiManager;

const char* PARAM_AREA = "area";
const char* PARAM_THRESHOLD = "threshold";
const char* PARAM_TAX = "tax";
#include <Ticker.h>
Ticker restartTicker;

void initNetwork() {
    wifiManager.setConnectTimeout(120);
    wifiManager.setAPCallback(handleWifiStatusMessage);
    wifiManager.autoConnect("Eldisplay");

    delay(2000);
    WiFi.setHostname("eldisplay");
    clearDisplay();
}

void setupWebServer(AsyncWebServer &server) {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", generateHTML());
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    });

    server.on("/config", HTTP_POST, [](AsyncWebServerRequest *request) {
            saveConfig(request); 
            request->send(200, "text/html", R"(
            <!DOCTYPE html>
            <html>
            <head>
                <meta charset="UTF-8">
                <meta http-equiv="refresh" content="10;url=/">
            </head>
            <body>
                <div class="box">
                    <h2>Inställningar sparade!</h2>
                    <p>Enheten startar om...</p>
                </div>
            </body>
            </html>
        )");

    restartTicker.once_ms(500, []() {
        ESP.restart();
    });


    });
    server.on("/toggleDisplay", HTTP_POST, [](AsyncWebServerRequest *request) {
        toggleDisplay();
        request->send(200, "text/plain", "Display toggled");
    });

    ElegantOTA.begin(&server);
    server.begin(); 
    ElegantOTA.onStart(displayUpdateMessage);
}

void saveConfig(AsyncWebServerRequest *request)
{
    if (request->hasParam(PARAM_AREA, true))    {
        String area = request->getParam(PARAM_AREA, true)->value();
        strncpy(priceArea, area.c_str(), sizeof(priceArea) - 1);
        priceArea[sizeof(priceArea) - 1] = '\0'; // Ensure null-termination

        saveChar("priceArea", priceArea);
    }

    if (request->hasParam(PARAM_THRESHOLD, true)) {
        threshold = request->getParam(PARAM_THRESHOLD, true)->value().toFloat();
        saveFloat("threshold", threshold);
    }
    if (request->hasParam(PARAM_TAX, true)) {
        addTax = request->getParam(PARAM_TAX, true);
        saveBool("addTax", addTax);
    }
    else {
        addTax = false;
        removeKey("addTax");
    }
    if (request->hasParam("nightMode", true)) {
        String nightModeValue = request->getParam("nightMode", true)->value();
        nightMode = (nightModeValue.equals("on")) ? true : false;
        saveBool("nightMode", nightMode);
    } else {
        nightMode = false;
        removeKey("nightMode");
    }

}

void handleWifiStatusMessage(WiFiManager *myWiFiManager) {
    displayConnectionFailedMessage();
}

void loopOTA(){
    ElegantOTA.loop();
}

String generateHTML(){
    String html = index_html;
    html.replace("{{area == 'SE1' ? 'selected' : ''}}", String(priceArea) == "SE1" ? "selected" : "");
    html.replace("{{area == 'SE2' ? 'selected' : ''}}", String(priceArea) == "SE2" ? "selected" : "");
    html.replace("{{area == 'SE3' ? 'selected' : ''}}", String(priceArea) == "SE3" ? "selected" : "");
    html.replace("{{area == 'SE4' ? 'selected' : ''}}", String(priceArea) == "SE4" ? "selected" : "");
    html.replace("{{threshold}}", String(threshold));
    bool isHigh = currentPrice > loadFloat("threshold", threshold);
    html.replace("{{currentPrice}}", String(currentPrice, 2));
    html.replace("{{priceColor}}", isHigh ? "#dc3545" : "#28a745");
    return html;
}

IPAddress getIP(){
    return WiFi.localIP();
}