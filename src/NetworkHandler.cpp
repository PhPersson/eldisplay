#include "NetworkHandler.h"
#include "DisplayHandler.h"


DNSServer dns; 
AsyncWebServer server(80);
AsyncWiFiManager wifiManager(&server, &dns);

const char* PARAM_AREA = "area";
const char* PARAM_THRESHOLD = "threshold";
const char* PARAM_TAX = "tax";



void initNetwork() {
    wifiManager.setAPCallback(handleWifiStatusMessage);
    wifiManager.setMinimumSignalQuality(10);
    wifiManager.autoConnect("Eldisplay","lampanlyser");
}


void setupMDNS(){
   if (!MDNS.begin("eldisplay")) 
   {             
     Serial.println("Error starting mDNS");
   }
}

void setHostname(){
    WiFi.setHostname("eldisplay");
}


void setupWebServer(AsyncWebServer &server) {

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = LittleFS.open("/index.html", "r").readString();
        html.replace("{{area}}", electricityPriceArea);
        html.replace("{{threshold}}", String(priceThreshold));
        html.replace("{{tax}}", shouldAddTax ? "checked" : "");
        request->send(200, "text/html", html);
    });

    server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404,"text/plain", "Not found");
    });

    server.on("/config", HTTP_POST, [] (AsyncWebServerRequest *request) {

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

void handleWifiStatusMessage(AsyncWiFiManager *myWiFiManage) {
    if (WiFi.status() == WL_CONNECTED) {
        displayConnectedMessage();
    } else {
        displayConnectionFailedMessage();
    }
}