#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <Adafruit_ILI9341.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <user_config.h>
#include <certs.h>


// Adds trsuted root-certs
BearSSL::X509List trustedRoots;

// Initialize the ILI9341 display 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
// NTP setup
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", 7200); // UTC+1


String getCurrentDate(){
  time_t rawTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&rawTime); 
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;

  return String(currentYear) + "/" + String(currentMonth) + "-" + String(monthDay);
}


void getElectricityPrices() {
  WiFiClientSecure client;
  HTTPClient http;
  client.setTrustAnchors(&trustedRoots);
  String url = api_url + getCurrentDate() + "_" + electricityPriceArea +".json"; // Dynamiclly use todays date using concatenation
  Serial.println(url);
  // http.begin(client,url);
  // int httpCode = http.GET(); // Make request to the api


  // if (httpCode > 0) {
  //   String payload = http.getString();
  //   Serial.println(payload);
  //   JsonDocument json;
  //   DeserializationError error = deserializeJson(json, payload);

  //   if (error) { // If there's any error deseralize the json in the response
  //     Serial.print("Failed to parse JSON: ");
  //     Serial.println(error.c_str());
  //     tft.fillScreen(ILI9341_BLACK); // Clears the screen before displaying new text
  //     tft.setCursor(10, 10); // Start at the top left
  //     tft.setTextColor(ILI9341_RED);
  //     tft.println("Could not parse response from API");
  //     return;
  //   }

  //   // Clear the screen before displaying data
  //   tft.fillScreen(ILI9341_BLACK);
  //   tft.setTextSize(2); // Change the text size
  //   tft.setCursor(80, 30);
  //   tft.setTextColor(ILI9341_WHITE);
  //   tft.println("Elpris:");

  // }
  // http.end();
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
  tft.setTextColor(ILI9341_YELLOW);
  tft.println(SSID); 
  WiFi.begin(SSID,WiFipassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }


  if (WiFi.status() == WL_CONNECTED) {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_GREEN);
    tft.println("Connected to WiFi"); 
  } else {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10); // Start at the top left
    tft.setTextColor(ILI9341_RED);
    tft.println("WiFi connection failed"); 
  }

  timeClient.begin();
  timeClient.update(); // Update to get current time
  trustedRoots.append(cert_ISRG_X1);
  trustedRoots.append(cert_ISRG_X2);

  getElectricityPrices();
}

void loop() {
}

