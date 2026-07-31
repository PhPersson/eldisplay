#include "webui.h"
#include "app_state.h"
#include "settings.h"
#include "web_not_found.h"
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

void setupWeb() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = index_html;
    html.replace("value=\"SE1\">SE1", priceArea == "SE1" ? "value=\"SE1\" selected>SE1" : "value=\"SE1\">SE1");
    html.replace("value=\"SE2\">SE2", priceArea == "SE2" ? "value=\"SE2\" selected>SE2" : "value=\"SE2\">SE2");
    html.replace("value=\"SE3\">SE3", priceArea == "SE3" ? "value=\"SE3\" selected>SE3" : "value=\"SE3\">SE3");
    html.replace("value=\"SE4\">SE4", priceArea == "SE4" ? "value=\"SE4\" selected>SE4" : "value=\"SE4\">SE4");
    html.replace("name=\"threshold\">", "name=\"threshold\" value=\"" + String(threshold, 2) + "\">");
    if (addTax) {
      html.replace("name=\"tax\" value=\"1\">", "name=\"tax\" value=\"1\" checked>");
    }
    request->send(200, "text/html", html);
  });



  server.on("/save", HTTP_GET, [](AsyncWebServerRequest *request) {
    String area = request->hasParam("area") ? request->getParam("area")->value() : "SE4";
    bool tax = request->hasParam("tax");
    float thresh = request->hasParam("threshold") ? request->getParam("threshold")->value().toFloat() : 1.0f;

    saveSettings(area, tax, thresh);

    request->send(200, "text/html",
      "<html><body><h3>Saved</h3><p>Restarting device...</p></body></html>");

    restartRequested = true;
  });


  server.onNotFound([](AsyncWebServerRequest *request) {
    String html = not_found_html;
    html.replace("%PATH%", request->url());
    request->send(404, "text/html", html);
  });

  server.begin();
}