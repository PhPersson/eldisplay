#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H
#include <WiFiManager.h>

#include "user_config.h"
#include "FileHandler.h"
#include <ESPmDNS.h>
#include <ElegantOTA.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;
extern WiFiManager wifiManager;

void initNetwork();
void setupWebServer(AsyncWebServer &server);
void handleWifiStatusMessage(WiFiManager *myWiFiManager);
void loopOTA();
void resetDevice();
#endif
