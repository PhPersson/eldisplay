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


  WiFi.begin(SSID,WiFipassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }


  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("WiFi connection failed");
  }

  trustedRoots.append(cert_ISRG_X1);
  trustedRoots.append(cert_ISRG_X2);

  getElectricityPrices();
}

void loop() {
}

