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
    #if defined(BOARD_GC9A01_ROUND)
        WiFi.setTxPower(WIFI_POWER_8_5dBm);
    #endif
    drawCenteredMessage("Connecting to WiFi");
    wifiManager.autoConnect("Eldisplay");
    drawCenteredMessage("Connect to Eldisplay");
    WiFi.setHostname("eldisplay");
    drawConnectedMessage("Connected OK");
    MDNS.begin("eldisplay");
}
