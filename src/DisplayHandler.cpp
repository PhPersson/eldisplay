#include "DisplayHandler.h"
#include "user_config.h"

// Initialize the display 
TFT_eSPI tft = TFT_eSPI();

void initDisplay() {
    tft.init();
    tft.setRotation(1); 
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
}

void displayConnectedMessage() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.drawString("Connected to WiFi", 120, 30);
}

void displayConnectionFailedMessage() {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Connect to AP:", 100, 30);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("Eldisplay", 100, 60);
}

void displayHttpErrorMessage(int httpCode) {
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2); 
    tft.drawString("API Request Error", 100, 60);
    tft.drawString("HTTP Code: " + String(httpCode), 10, 90);
}

void displayMDNS() {
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setTextSize(1); // Text size
    tft.drawString("eldisplay.local", 120, tft.height() - 30); 
}

void displayNoValuesMessage() {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("To setup device", 100, 30);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("eldisplay.local", 100, 60);
}


void displayEnergyMessage(int startOfHour, float totalSekPerKwh, int hoursDisplayed, uint16_t textColor) {
    tft.setTextColor(textColor);
    int yPos = 80 + (hoursDisplayed * 40);
    tft.drawString(String(startOfHour) + ": SEK: " + String(totalSekPerKwh, 2), 80, yPos);
}

void displayDeviceText() {
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Elpris:", 120, 30);
}

void displayJsonError(const String& error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK); 
    tft.setTextSize(2);
    tft.drawString("Error from API:", 10, 60);
    tft.drawString(error, 10, 90);
}
