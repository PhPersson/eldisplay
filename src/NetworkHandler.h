#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include "ESPAsyncHTTPUpdateServer.h"
#include "user_config.h"
#include "FileHandler.h"



#include <ESPmDNS.h>


extern AsyncWebServer server;
extern WiFiManager wifiManager;
extern ESPAsyncHTTPUpdateServer _updateServer;


void initNetwork();
void handleWifiStatusMessage(WiFiManager *myWiFiManage);

void setupMDNS();
void setHostname();
void setupWebServer(AsyncWebServer &server);


#endif
