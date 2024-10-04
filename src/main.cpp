#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <user_config.h>

void getElectricityPrices() {
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure(); // Only during testing!!

  http.begin(client,api_url);
  int httpCode = http.GET(); // Make request to the api


  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  }
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
  getElectricityPrices();
}

void loop() {
}

