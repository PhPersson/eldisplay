#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <Adafruit_ILI9341.h>
#include <user_config.h>
#include <certs.h>


// Adds trsuted root-certs
BearSSL::X509List trustedRoots;

// Initialize the ILI9341 display 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


void getElectricityPrices() {
  WiFiClientSecure client;
  HTTPClient http;
  client.setTrustAnchors(&trustedRoots);

  http.begin(client,api_url);
  int httpCode = http.GET(); // Make request to the api


  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  }
  http.end();
}


void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(0); // Horizontal mode on the screen

  tft.fillScreen(ILI9341_BLACK); // Clears the screen before displaying new text
  tft.setTextColor(ILI9341_WHITE); // Sets text color to white
  tft.setTextSize(2); // Text size

  tft.setCursor(10, 10); // Start at the top left

  tft.println("Connecting to WiFi"); 
  tft.setCursor(10, 50);
  tft.println(SSID); 
  WiFi.begin(SSID,WiFipassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }


  if (WiFi.status() == WL_CONNECTED) {
    tft.println("Connected to WiFi"); 
  } else {
    tft.println("WiFi connection failed"); 
  }

  trustedRoots.append(cert_ISRG_X1);
  trustedRoots.append(cert_ISRG_X2);

  getElectricityPrices();
}

void loop() {
}

