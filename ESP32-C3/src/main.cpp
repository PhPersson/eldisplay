#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LovyanGFX.hpp>
#include <WiFiManager.h> 
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
Preferences prefs;
AsyncWebServer server(80);
#include "webui.h"

String priceArea = "SE4";
bool addTax = false;
float threshold = 1.0f;

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_GC9A01 _panel_instance;
  lgfx::Bus_SPI _bus_instance;

public:
  LGFX() {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = SPI2_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 10000000;
      cfg.freq_read = 8000000;
      cfg.spi_3wire = false;
      cfg.use_lock = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = 4;
      cfg.pin_mosi = 3;
      cfg.pin_miso = -1;
      cfg.pin_dc = 10;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs = 1;
      cfg.pin_rst = 0;
      cfg.pin_busy = -1;
      cfg.panel_width = 240;
      cfg.panel_height = 240;
      cfg.memory_width = 240;
      cfg.memory_height = 240;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = false;
      cfg.invert = true;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = false;
      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance);
  }
};

LGFX lcd;
WiFiClientSecure client;


float currentPrice = 0.0f;

float applyTax(float price) {
  if (addTax) {
    price = price * 1.25f + 0.535f;
  }
  return roundf(price * 100.0f) / 100.0f;
}

uint16_t priceColor(float price) {
  return price > threshold ? TFT_RED : TFT_GREEN;
}

String todayPath() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo, 1000)) {
    return "";
  }

  char buf[64];
  strftime(buf, sizeof(buf), "/api/v1/prices/%Y/%m-%d_", &timeinfo);
  return String(buf) + priceArea + ".json?unit=kr";
}

void drawCenteredPrice(float price) {
  lcd.fillScreen(TFT_BLACK);

  lcd.setFont(&fonts::Font8);
  lcd.setTextColor(priceColor(price), TFT_BLACK);

  String text = String(price, 2);
  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 95;

  lcd.setCursor(x, y);
  lcd.print(text);
}

void drawCenteredMessage(const String& text) {
  lcd.fillScreen(TFT_BLACK);

  lcd.setFont(&fonts::Font4);
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);

  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 110;

  lcd.setCursor(x, y);
  lcd.print(text);
}
void drawConnectedMessage(const String& text) {
  lcd.fillScreen(TFT_BLACK);

  lcd.setFont(&fonts::Font4);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);

  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 110;

  lcd.setCursor(x, y);
  lcd.print(text);
}


bool fetchCurrentPrice() {
  HTTPClient http;
  String url = String("https://se.elpris.eu") + todayPath();
  client.stop();
  client.setInsecure();

  if (!http.begin(client, url)) {
    Serial.println("http.begin() failed");
    return false;
  }

  int httpCode = http.GET();

  if (httpCode <= 0) {
    drawCenteredMessage("HTTP error: " + http.errorToString(httpCode));
    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  JsonDocument json;
  DeserializationError error = deserializeJson(json, payload);
  if (error) {
    return false;
  }

  int stepSeconds = json["s"] | 900;
  String t0 = String((const char*)json["t0"]);
  JsonArray data = json["p"].as<JsonArray>();

  if (data.isNull() || data.size() == 0) {
    drawCenteredMessage("No price data");
    return false;
  }

  struct tm nowInfo;
  if (!getLocalTime(&nowInfo, 1000)) {
    drawCenteredMessage("No time loaded");
    return false;
  }

  int currentIndex = nowInfo.tm_hour * 4 + (nowInfo.tm_min / 15);

  if (currentIndex < 0 || currentIndex >= data.size()) {
    Serial.println("Index out of range");
    return false;
  }

  currentPrice = applyTax(data[currentIndex].as<float>());
  return true;
}


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
    
}

void setupTime() {
  configTime(0, 0, "pool.ntp.org");
  setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
  tzset();

  struct tm timeinfo;
  int retries = 0;
  while (!getLocalTime(&timeinfo, 1000) && retries < 20) {
    delay(500);
    retries++;
  }
}

void loadSettings() {
  prefs.begin("elpris", true);
  priceArea = prefs.getString("area", "SE4");
  addTax = prefs.getBool("tax", false);
  threshold = prefs.getFloat("thresh", 1.0f);
  prefs.end();
}

void saveSettings(const String& area, bool tax, float thresh) {
  prefs.begin("elpris", false);
  prefs.putString("area", area);
  prefs.putBool("tax", tax);
  prefs.putFloat("thresh", thresh);
  prefs.end();

  priceArea = area;
  addTax = tax;
  threshold = thresh;
}

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
      "<html><body><h3>Saved</h3><p>Restarting...</p></body></html>");
  });

  server.begin();
}


unsigned long lastFetch = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  lcd.init();
  lcd.setRotation(0);
  lcd.setBrightness(180);
  drawCenteredMessage("Starting up");
  loadSettings();
  delay(2500);
  connectWifi();
  setupTime();
  setupWeb();

  if (fetchCurrentPrice()) {
    drawCenteredPrice(currentPrice);
  } else {
    drawCenteredMessage("Fel");
  }

  lastFetch = millis();
}

void loop() {
  if (millis() - lastFetch > 5UL * 60UL * 1000UL) {
    if (fetchCurrentPrice()) {
      drawCenteredPrice(currentPrice);
    } else {
      drawCenteredMessage("Fel");
    }
    lastFetch = millis();
  }

  delay(250);
}