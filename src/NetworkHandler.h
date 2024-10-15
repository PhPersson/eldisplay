
#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <ESP8266mDNS.h>
#include "user_config.h"
#include "FileHandler.h"
#include "LittleFS.h"


extern DNSServer dns; 
extern AsyncWebServer server;
extern AsyncWiFiManager wifiManager;

void initNetwork();
void handleWifiStatusMessage(AsyncWiFiManager *myWiFiManage);


void setupMDNS();
void setHostname();
void setupWebServer(AsyncWebServer &server);

#endif
