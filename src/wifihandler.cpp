#include "WiFiHandler.h"

// Define your server and DNS variables here
AsyncWebServer server(80);
DNSServer dns;

void setupWiFi() {
    AsyncWiFiManager wifiManager(&server, &dns);
    wifiManager.setAPCallback(handleWiFiStatus());
    wifiManager.autoConnect("Eldisplay", "lampanlyser");

    WiFi.hostname("eldisplay");

}

void setupLittleFS() {
    // Begin LittleFS
    if (!LittleFS.begin()) {
        Serial.println("An Error has occurred while mounting LittleFS");
    }
}

void setupMDNS() {
    // Start mDNS at esp8266.local address
    if (!MDNS.begin("eldisplay")) {             
        Serial.println("Error starting mDNS");
    }
}


void handleWiFiStatus(ILI9341 tft) {
    if (WiFi.status() == WL_CONNECTED) {
        tft.fillScreen(ILI9341_BLACK);
        tft.setCursor(10, 10);
        tft.setTextColor(ILI9341_GREEN);
        tft.println("Connected to WiFi");
        tft.setTextColor(ILI9341_YELLOW);
        tft.setCursor(10, 50);
    } else {
        tft.fillScreen(ILI9341_BLACK);
        tft.setCursor(20, 10);
        tft.setTextColor(ILI9341_RED);
        tft.println("WiFi connection failed");
        tft.println("Connect to AP:");
        tft.setTextColor(ILI9341_YELLOW);
        tft.println("Eldisplay");
    }
}
