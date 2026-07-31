#include "wifi_manager.h"
#include "display_manager.h"
#include <WiFi.h>
#include <WiFiManager.h> 
#include <ESPmDNS.h>

void connectWifi() {
    WiFi.mode(WIFI_STA);
    delay(1000);
    WiFiManager wifiManager;
    wifiManager.setConnectTimeout(120);
    WiFi.setTxPower(WIFI_POWER_8_5dBm);
    drawCenteredMessage("Connecting to WiFi");
    wifiManager.autoConnect("Eldisplay");
    drawCenteredMessage("Connect to Eldisplay");
    WiFi.setHostname("eldisplay");
    drawConnectedMessage("Connected OK");
    MDNS.begin("eldisplay");
}
