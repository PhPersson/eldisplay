#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

// Function to set up the web server routes
void setupWebServer(AsyncWebServer &server);

// Function to handle 404 (Not Found) errors
void notFound(AsyncWebServerRequest *request);

#endif // WEBSERVERHANDLER_H