#include "wifi_manager.h"
#include "display_manager.h"
#include <WiFi.h>
#include <WiFiManager.h> 
#include <ESPmDNS.h>

void connectWifi() {
    WiFi.setHostname("eldisplay");

    WiFi.mode(WIFI_STA);

    WiFiManager wifiManager;

    wifiManager.setConnectTimeout(120);
    wifiManager.setAPCallback(handleWifiStatusMessage);

    drawCenteredMessage("Connecting...");

    bool connected = wifiManager.autoConnect("Eldisplay");

    if (!connected) {
        drawCenteredMessage("WiFi failed");
        Serial.println("WiFi connection failed");

        delay(3000);
    }

    String message = "Connected to WiFi:" + WiFi.SSID();
    drawConnectedMessage(message.c_str());
    MDNS.begin("eldisplay");
    delay(2000);
}
void handleWifiStatusMessage(WiFiManager *myWiFiManager) {
    displayConnectionFailedMessage();
}
