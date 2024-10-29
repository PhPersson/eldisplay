#include "NetworkHandler.h"
#include "DisplayHandler.h"


AsyncWebServer server(80);
WiFiManager wifiManager;
ESPAsyncHTTPUpdateServer _updateServer;

const char* PARAM_AREA = "area";
const char* PARAM_THRESHOLD = "threshold";
const char* PARAM_TAX = "tax";


#define index_html_len 1269
const uint8_t index_html[] PROGMEM = {  0x1F, 0x8B, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x9D, 0x57, 0x5F, 0x6F, 0xDB, 0x36, 0x10, 0x7F, 0x1F, 0xB0, 0xEF, 0x70, 0x63, 0x50, 0xD4, 0x2E, 0x22, 0xDB, 0x72, 0xE2, 0xCE, 0x75, 0x25, 0x77, 0x45, 0x9B, 0x61, 0x7B, 0x18, 0x5A, 0x34, 0xD9, 0xC3, 0x30, 0xF4, 0x81, 0x96, 0x28, 0x8B, 0x30, 0x45, 0xA9, 0x24, 0xE5, 0x38, 0x2B, 0xFC, 0xB6, 0x7D, 0x93, 0xE6, 0x2B, 0xEC, 0x0B, 0xF8, 0x8B, 0xED, 0xF4, 0xCF, 0xA2, 0x1D, 0xC5, 0x2D, 0x86, 0x24, 0xB2, 0xC5, 0x3B, 0xDE, 0xFD, 0xEE, 0x77, 0x77, 0xE4, 0xC5, 0xFB, 0xE1, 0xED, 0xBB, 0x37, 0x37, 0x7F, 0xBC, 0xBF, 0x82, 0xD8, 0x24, 0x62, 0xFE, 0xFD, 0x77, 0x5E, 0xF1, 0x09, 0x82, 0xCA, 0xA5, 0x4F, 0xF4, 0x9A, 0xCC, 0xA1, 0x58, 0x62, 0x34, 0x44, 0x11, 0x80, 0x97, 0x30, 0x43, 0x21, 0x88, 0xA9, 0xD2, 0xCC, 0xF8, 0xE4, 0xF7, 0x9B, 0x9F, 0x9D, 0x69, 0xA9, 0x82, 0x22, 0xC3, 0x8D, 0x60, 0xF3, 0x2B, 0x11, 0x72, 0x9D, 0x09, 0x7A, 0xE7, 0x0D, 0xAB, 0x05, 0x68, 0xF7, 0x49, 0x9A, 0x30, 0x9F, 0xAC, 0x39, 0xBB, 0xCD, 0x52, 0x65, 0x08, 0x04, 0xA9, 0x34, 0x4C, 0xA2, 0x9D, 0x5B, 0x1E, 0x9A, 0xD8, 0x0F, 0xD9, 0x9A, 0x07, 0xCC, 0x29, 0x5F, 0xCE, 0x81, 0x4B, 0x6E, 0x38, 0x15, 0x8E, 0x0E, 0xA8, 0x60, 0xBE, 0x3B, 0x18, 0x91, 0x0A, 0x81, 0x36, 0x77, 0x68, 0xB5, 0xF8, 0x0A, 0xB0, 0x48, 0xC3, 0x3B, 0xF8, 0x0C, 0xD5, 0x0B, 0x40, 0x84, 0xF6, 0x9C, 0x88, 0x26, 0x5C, 0xDC, 0xCD, 0xE0, 0xB5, 0xC2, 0xDD, 0xE7, 0xA0, 0xA9, 0xD4, 0x8E, 0x66, 0x8A, 0x47, 0x2F, 0xF7, 0x7A, 0x0B, 0x1A, 0xAC, 0x96, 0x2A, 0xCD, 0x65, 0xE8, 0x04, 0xA9, 0x48, 0xD5, 0x0C, 0xCE, 0xA2, 0x4B, 0xFC, 0x79, 0xD1, 0xAA, 0x24, 0x54, 0x2D, 0xB9, 0x9C, 0xC1, 0xA8, 0x5D, 0xCA, 0x68, 0x18, 0x72, 0xB9, 0x9C, 0xC1, 0x78, 0x94, 0x6D, 0x9A, 0xE5, 0x6D, 0xF5, 0x31, 0x88, 0x52, 0x95, 0x58, 0x48, 0xBA, 0x3C, 0x44, 0xD1, 0x57, 0x6C, 0x15, 0xF1, 0xA8, 0x90, 0x29, 0x47, 0xD1, 0x90, 0xE7, 0x7A, 0x06, 0xEE, 0x91, 0x70, 0xE3, 0xE8, 0x98, 0x86, 0xE9, 0x2D, 0xC2, 0x82, 0x71, 0xB6, 0x81, 0x09, 0xFE, 0xA9, 0xE5, 0x82, 0xF6, 0x46, 0xE7, 0x50, 0xFF, 0x0E, 0xDC, 0xBE, 0x1D, 0xC4, 0xA6, 0x62, 0x73, 0x06, 0x97, 0xA3, 0x03, 0x5B, 0x4D, 0x78, 0x34, 0x37, 0xE9, 0x51, 0x28, 0xB1, 0x6B, 0xC5, 0x61, 0xD8, 0xC6, 0x38, 0x54, 0xF0, 0x25, 0xEA, 0x06, 0x98, 0x2A, 0xA6, 0x5A, 0x1B, 0x4D, 0x60, 0x17, 0x17, 0x17, 0x47, 0x26, 0x04, 0x5D, 0x30, 0x61, 0x59, 0xA9, 0x2B, 0x62, 0x06, 0x0B, 0x91, 0x06, 0xAB, 0x63, 0x14, 0xCE, 0x22, 0x35, 0x26, 0x4D, 0x8E, 0xC3, 0x2D, 0x93, 0x79, 0xCB, 0xF8, 0x32, 0x36, 0xB8, 0x31, 0x15, 0xE1, 0x43, 0xCF, 0x93, 0xC9, 0xE4, 0xC8, 0x33, 0x97, 0x59, 0x6E, 0xFE, 0x34, 0x77, 0x19, 0xF3, 0x9F, 0x16, 0xD8, 0x9F, 0x7E, 0x3C, 0x87, 0x87, 0x12, 0x99, 0x27, 0x0B, 0xA6, 0x9E, 0x7E, 0xB4, 0x20, 0xD6, 0x34, 0xB9, 0xA3, 0xD1, 0x93, 0x8E, 0x2C, 0xB9, 0x1D, 0xE4, 0xED, 0x61, 0x9F, 0x4C, 0xE1, 0xE4, 0xA1, 0x0C, 0xCD, 0x61, 0xDE, 0x74, 0x2A, 0x78, 0x08, 0x67, 0x41, 0x10, 0x9C, 0x08, 0x21, 0x88, 0x59, 0xB0, 0xC2, 0xBC, 0x1F, 0x40, 0xAD, 0xDD, 0xAB, 0x8A, 0x19, 0xB7, 0xA3, 0x18, 0x17, 0x39, 0x22, 0x93, 0x4E, 0xD1, 0x5E, 0x94, 0x4B, 0xA6, 0xBA, 0x52, 0x11, 0x09, 0x66, 0x93, 0x8D, 0x6F, 0x4E, 0xC8, 0x15, 0x0B, 0x0C, 0x4F, 0x8B, 0x5C, 0xA7, 0x22, 0x4F, 0x64, 0x2B, 0x5F, 0xD2, 
0xAC, 0xD3, 0x95, 0x0D, 0x56, 0xE7, 0x8B, 0x84, 0x9B, 0x03, 0xA8, 0x8F, 0x10, 0xF8, 0x2D, 0x1C, 0xC9, 0x54, 0xB2, 0xA3, 0x62, 0xD0, 0xFC, 0x2F, 0x86, 0xA6, 0x9E, 0xDB, 0xEA, 0x41, 0xAE, 0x74, 0x51, 0x0B, 0x59, 0xCA, 0x3B, 0xAB, 0xF3, 0x36, 0xE6, 0xC6, 0xB2, 0xD3, 0xD1, 0x97, 0xE3, 0x29, 0xFD, 0xF1, 0xF2, 0x54, 0x1D, 0x35, 0x71, 0xCD, 0xE2, 0x74, 0x7D, 0xC0, 0x65, 0x97, 0x31, 0x77, 0x3A, 0xBD, 0x98, 0x1E, 0xE7, 0x23, 0x35, 0xD4, 0xA9, 0x72, 0x72, 0x72, 0xB7, 0x28, 0x32, 0xAA, 0x57, 0x77, 0x0B, 0x91, 0xB3, 0xAF, 0x05, 0xF2, 0x3F, 0x98, 0x3D, 0xD5, 0xCB, 0xA5, 0x2C, 0x64, 0x41, 0xAA, 0x68, 0x55, 0x00, 0x87, 0xF4, 0x77, 0x37, 0xF0, 0xC3, 0xF0, 0xBE, 0x81, 0x22, 0x3C, 0xAF, 0x7A, 0xAE, 0xFB, 0xFC, 0x1C, 0xDC, 0x29, 0x3E, 0xC6, 0xA3, 0x17, 0x7D, 0xCB, 0x5C, 0x6D, 0x50, 0x31, 0xBC, 0x5D, 0xF6, 0x8C, 0x9D, 0xB0, 0xC5, 0xC2, 0x97, 0x9D, 0x34, 0x9D, 0x08, 0xB9, 0x9B, 0xC0, 0x13, 0xFC, 0x9D, 0xA6, 0xE8, 0xDB, 0x18, 0xB2, 0x03, 0x6A, 0x38, 0x7A, 0x3C, 0xAC, 0x90, 0xAA, 0x55, 0x1B, 0xDA, 0x9E, 0x96, 0xE1, 0x33, 0xF8, 0x2D, 0x5D, 0x70, 0xC1, 0xA0, 0xB8, 0x02, 0x11, 0x3B, 0x3C, 0x1B, 0x56, 0x92, 0x9F, 0x12, 0x16, 0x72, 0x0A, 0x3D, 0xEB, 0xBC, 0x7F, 0x5E, 0x9C, 0xF7, 0x7D, 0xCB, 0x4B, 0x75, 0x53, 0x1E, 0x95, 0xCD, 0xB6, 0xED, 0xAF, 0xF2, 0xFA, 0x6A, 0xC5, 0x93, 0x03, 0x71, 0x79, 0x27, 0xD8, 0x3D, 0x38, 0x18, 0xB3, 0xC4, 0x92, 0x3F, 0x7E, 0xEC, 0x76, 0x1F, 0xBC, 0xAD, 0xF4, 0xE1, 0x59, 0x35, 0x87, 0x67, 0x2D, 0xEC, 0xC3, 0xCE, 0x47, 0x9F, 0xAD, 0x60, 0x8F, 0x75, 0x6A, 0x25, 0x69, 0x6B, 0xF1, 0xEE, 0x0D, 0xDB, 0x51, 0xC1, 0xD3, 0x81, 0xE2, 0x99, 0xA9, 0xC7, 0x86, 0x28, 0x97, 0xE5, 0x39, 0x57, 0x0C, 0x20, 0x11, 0x57, 0xC9, 0x87, 0x22, 0x3D, 0x3D, 0xB6, 0xC6, 0x0A, 0xB1, 0x28, 0x2B, 0xDF, 0x07, 0x99, 0x2A, 0x3F, 0xDF, 0xB2, 0x88, 0xE6, 0xC2, 0xF4, 0xFA, 0x56, 0xC1, 0x49, 0x6D, 0x20, 0xC7, 0xD1, 0xE2, 0x4D, 0x65, 0x85, 0x85, 0xE0, 0x37, 0x16, 0x7B, 0x64, 0xF7, 0xB7, 0x82, 0x30, 0x07, 0xBD, 0xFB, 0xB2, 0xC2, 0xA0, 0xB2, 0xDD, 0x3D, 0x50, 0x63, 0x8A, 0x95, 0x35, 0x17, 0x02, 0x76, 0xF7, 0x58, 0x8B, 0xDA, 0xEC, 0xBE, 0x08, 0x41, 0xC1, 0x14, 0x2B, 0x11, 0x5D, 0x28, 0xBE, 0xD2, 0x5C, 0x56, 0xAB, 0x12, 0x43, 0xA3, 0xEA, 0x15, 0x69, 0xFD, 0xF1, 0x08, 0x7A, 0x07, 0xDE, 0xFA, 0x36, 0x4D, 0xB7, 0x5C, 0xE2, 0x60, 0x30, 0xC0, 0xE2, 0x2B, 0xAB, 0x73, 0x10, 0x2B, 0x16, 0x21, 0x1C, 0x32, 0x2C, 0x4B, 0x8F, 0xB4, 0xAD, 0x7C, 0xC4, 0x50, 0x43, 0x8B, 0x37, 0xAC, 0x67, 0x3C, 0xAF, 0xA8, 0x94, 0x8A, 0xB3, 0xD8, 0x9D, 0xFF, 0x7A, 0x00, 0x07, 0x95, 0xDC, 0x79, 0x55, 0x8E, 0x5E, 0xC8, 0xD7, 0x10, 0x08, 0xAA, 0xB5, 0x4F, 0x8A, 0xE2, 0x21, 0x35, 0xB5, 0x5E, 0x59, 0x49, 0xB4, 0xA4, 0xD7, 0x27, 0xC3, 0x92, 0x8E, 0x25, 0x01, 0x1C, 0xFF, 0xE2, 0x34, 0xF4, 0xC9, 0xFB, 0x77, 0xD7, 0x37, 0x8D, 0x2A, 0x2A, 0x57, 0x83, 0x02, 0x6E, 0xF1, 0x09, 0x55, 0x8C, 0x12, 0x9C, 0x1E, 0x33, 0xC5, 0x75, 0x9A, 0xA8, 0xDD, 0x7D, 0xC8, 0x66, 0xDE, 0xB0, 0x54, 0x68, 0xF5, 0xCB, 0x5A, 0x82, 0xB2, 0x96, 0x48, 0x51, 0x67, 0x04, 0x78, 0x58, 0x6F, 0xAD, 0x87, 0xCB, 0xEA, 0x7B, 0xC2, 0xA5, 0x60, 0x72, 0x89, 0x33, 0x25, 0xB9, 0x20, 0xC5, 0x18, 0x64, 0xBD, 0x29, 0xF6, 0x29, 0xC7, 0x8B, 0x2E, 0x04, 
0xEC, 0xD7, 0x80, 0xC5, 0x38, 0x58, 0x30, 0x74, 0xFF, 0x5A, 0x2E, 0x19, 0x30, 0xDB, 0x3B, 0xF4, 0xAE, 0xAF, 0xDC, 0x73, 0xB8, 0xBE, 0x1A, 0x17, 0x8F, 0x8B, 0xE2, 0x71, 0xD9, 0x27, 0xF3, 0xA6, 0x1B, 0x0F, 0xD1, 0x1B, 0xE4, 0x5B, 0x17, 0xB6, 0xC8, 0xFC, 0x97, 0xDD, 0xBF, 0x4B, 0x53, 0x9B, 0x3A, 0x1D, 0x41, 0xD5, 0x0D, 0x55, 0x0C, 0xAD, 0x81, 0x3A, 0x10, 0x6B, 0x41, 0x1B, 0x96, 0xF9, 0x64, 0x34, 0x18, 0xB9, 0x04, 0xD6, 0x14, 0x2F, 0x07, 0x9F, 0x7C, 0xFE, 0xBC, 0x97, 0x6F, 0xB7, 0xA4, 0x23, 0x14, 0xB9, 0xFB, 0xA2, 0x6A, 0x10, 0xCC, 0x80, 0x5E, 0x51, 0x50, 0x58, 0x89, 0x92, 0x6A, 0x1C, 0x3C, 0x12, 0x88, 0x0B, 0x8C, 0x8F, 0xC6, 0x42, 0x37, 0x6D, 0x8A, 0x8E, 0x20, 0x37, 0x03, 0x49, 0x0D, 0x1A, 0x35, 0x1B, 0xB8, 0xC5, 0x57, 0x44, 0x45, 0x37, 0xDB, 0xED, 0x1C, 0x3E, 0x94, 0xBE, 0xB0, 0xF5, 0x21, 0x49, 0x13, 0xFD, 0x0A, 0x7A, 0xE3, 0xC9, 0x93, 0xFE, 0xDE, 0xD7, 0x9E, 0x93, 0xFD, 0x8A, 0x55, 0x4C, 0xC7, 0xE7, 0xC1, 0xA3, 0x50, 0xAA, 0x6B, 0x79, 0xCF, 0xC8, 0x75, 0x46, 0x15, 0x3D, 0x50, 0xA6, 0x50, 0x34, 0x01, 0x16, 0x21, 0xDE, 0x4F, 0xA4, 0x31, 0xDF, 0xDE, 0x55, 0x64, 0xFE, 0xEE, 0xE6, 0xB5, 0x37, 0xA4, 0x5D, 0x5B, 0xCE, 0xF6, 0xFA, 0xF6, 0xC9, 0x4D, 0x20, 0x95, 0x81, 0xE0, 0xC1, 0x0A, 0x79, 0x78, 0x78, 0x70, 0x90, 0xF9, 0xEE, 0x9F, 0x7D, 0x53, 0x9F, 0xE8, 0x69, 0xDB, 0xA5, 0x37, 0xC4, 0xC8, 0x9B, 0xCE, 0x19, 0x16, 0xAD, 0x53, 0x75, 0x5E, 0xBD, 0xEC, 0x0D, 0xEB, 0x66, 0xC4, 0xC6, 0xAB, 0xFE, 0x39, 0xFB, 0x0F, 0x2E, 0x30, 0x09, 0x8A, 0xAE, 0x0D, 0x00, 0x00 };


void initNetwork() {
    wifiManager.setConnectTimeout(120);
    wifiManager.autoConnect("Eldisplay");
    if (!MDNS.begin("eldisplay")) 
   {             
     Serial.println("Error starting mDNS");
   }
   WiFi.setHostname("eldisplay");
}

void setupWebServer(AsyncWebServer &server) {
    _updateServer.setup(&server, "/ota", "eldisplay", "billigel");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse* response = request->beginResponse_P(200, "text/html", index_html, sizeof(index_html));
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    });

    server.on("/config", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam(PARAM_AREA, true)) {
            String area = request->getParam(PARAM_AREA, true)->value();
            strncpy(electricityPriceArea, area.c_str(), sizeof(electricityPriceArea) - 1);
            electricityPriceArea[sizeof(electricityPriceArea) - 1] = '\0';  // Ensure null-termination
            
            saveChar("electricityPriceArea", electricityPriceArea); // Save to Preferences
        }

        if (request->hasParam(PARAM_THRESHOLD, true)) {
            priceThreshold = request->getParam(PARAM_THRESHOLD, true)->value().toFloat();
            saveFloat("priceThreshold", priceThreshold); // Save to Preferences
        }

        shouldAddTax = request->hasParam(PARAM_TAX, true); // Simplified boolean assignment
        saveBool("shouldAddTax", shouldAddTax); // Save to Preferences
        
        request->send(200, "text/plain", "Settings updated. Restarting..."); // Respond to the client
        delay(1000); // Optional: give some time to see the message
        ESP.restart(); // Restart the ESP
    });


    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    factoryReset();
    request->send(200, "text/plain", "Rebooting.....");
    delay(5000);
    ESP.restart();
    });

    server.begin(); 
}

void handleWifiStatusMessage() {
    if (WiFi.status() == WL_CONNECTED) {
        displayConnectedMessage();
    } else {
        displayConnectionFailedMessage();
    }
}