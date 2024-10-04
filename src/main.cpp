#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <user_config.h>



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
}

void loop() {
  // put your main code here, to run repeatedly:
}

