#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H
#include <WiFiManager.h>

#include "user_config.h"
#include "FileHandler.h"
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>


extern AsyncWebServer server;
extern WiFiManager wifiManager;

void initNetwork();
void setupWebServer(AsyncWebServer &server);
void handleWifiStatusMessage(WiFiManager *myWiFiManager);
void loopOTA();
String generateHTML();

void handleToggleNightMode(AsyncWebServerRequest *request);

#endif
