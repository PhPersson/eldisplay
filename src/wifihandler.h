#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <ESPAsyncWiFiManager.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>
#include <Adafruit_ILI9341.h>

void setupWiFi();
void setupLittleFS();
void setupMDNS();


#endif // WIFIHANDLER_H
