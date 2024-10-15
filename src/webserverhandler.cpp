#include "WebServerHandler.h"

void setupWebServer(AsyncWebServer &server) {
    // Route for root index.html
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });

    // Route for handling not found (404) errors
    server.onNotFound(notFound);

    // Start the server
    server.begin();
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
