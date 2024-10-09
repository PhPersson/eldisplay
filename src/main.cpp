#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <Adafruit_ILI9341.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>
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
  struct tm *ptm = gmtime(&rawTime);

  char dateStr[12];
  strftime(dateStr, sizeof(dateStr), "%Y/%m-%d", ptm);
  return String(dateStr);
}


void getElectricityPrices() {
  WiFiClientSecure client;
  HTTPClient http;
  client.setTrustAnchors(&trustedRoots);
  String url = api_url + getCurrentDate() + "_" + electricityPriceArea +".json"; // Dynamiclly use todays date using concatenation
  http.begin(client,url);
  int httpCode = http.GET(); // Make request to the api


  if (httpCode > 0) {
    String payload = http.getString();
    JsonDocument json;
    DeserializationError error = deserializeJson(json, payload);

    if (error) { // If there's any error deseralize the json in the response
      Serial.print("Failed to parse JSON: ");
      Serial.println(error.c_str());
      tft.fillScreen(ILI9341_BLACK); // Clears the screen before displaying new text
      tft.setCursor(10, 10);
      tft.setTextColor(ILI9341_RED);
      tft.println("Error from API");
      tft.setCursor(10, 40);
      tft.println(error.c_str());
      return;
    }

    // Clear the screen before displaying data
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2); // Change the text size
    tft.setCursor(80, 30);
    tft.setTextColor(ILI9341_WHITE);
    tft.println("Elpris:");

    int currentHour = timeClient.getHours();
    int hoursDisplayed = 0;
    
    for (size_t i = 0; i < json.size(); i++) {
      String timeStart(json[i]["time_start"]);
      int startOfHour = timeStart.substring(11,13).toInt(); //Split the time string and extract only the hour
    
      // Check if the current hour or next two hours are matched
      if (startOfHour == currentHour || startOfHour == (currentHour + 1) % 24 || startOfHour == (currentHour + 2) % 24) {
      float sekPerKwh = json[i]["SEK_per_kWh"];
      float totalSekPerKwh = 0;
      totalSekPerKwh = sekPerKwh;
      totalSekPerKwh = round(totalSekPerKwh * 100.0) / 100.0; // Round to 2 decimal places

      // Display the extracted data
      tft.setCursor(30, 80 + (hoursDisplayed * 40));
      tft.printf("%02d: SEK: %.2f", startOfHour, totalSekPerKwh);
      hoursDisplayed++;

      if (hoursDisplayed >= 3) {
        break;
      }

      }
    }
  }


  else {
  Serial.print("Error on HTTP request: ");
  Serial.println(httpCode);
  tft.setCursor(10, 60);
  tft.setTextColor(ILI9341_RED);
  tft.println("Error when requesting API");
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

  tft.println("Starting AP");
  WiFiManager wifiManager;
  wifiManager.autoConnect("Eldisplay");
  

  if (WiFi.status() == WL_CONNECTED) {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_GREEN);
    tft.println("Connected to WiFi");
    tft.println("");
    tft.println(wifiManager.getWiFiSSID());
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