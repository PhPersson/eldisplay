#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LovyanGFX.hpp>
#include <WiFiManager.h> 

const char* PRICE_AREA = "SE4";
const bool ADD_TAX = false;
const float THRESHOLD = 1.0f;

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
  if (ADD_TAX) {
    price = price * 1.25f + 0.535f;
  }
  return roundf(price * 100.0f) / 100.0f;
}

uint16_t priceColor(float price) {
  return price > THRESHOLD ? TFT_RED : TFT_GREEN;
}

String todayPath() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo, 1000)) {
    return "";
  }

  char buf[64];
  strftime(buf, sizeof(buf), "/api/v1/prices/%Y/%m-%d_", &timeinfo);
  return String(buf) + PRICE_AREA + ".json?unit=kr";
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
  Serial.println("Gjorde en förfrågan");
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

unsigned long lastFetch = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  lcd.init();
  lcd.setRotation(0);
  lcd.setBrightness(180);
  drawCenteredMessage("Starting up");
  delay(2500);
  connectWifi();
  setupTime();

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