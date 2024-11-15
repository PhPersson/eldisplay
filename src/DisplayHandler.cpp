#include "DisplayHandler.h"
#include "user_config.h"

TFT_eSPI tft = TFT_eSPI();

void initDisplay() {
    tft.init();
    tft.setRotation(1); 
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
}

void displayConnectionFailedMessage() {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Connect to AP:", 80, 80);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("Eldisplay", 80, 120);
}

void displayHttpErrorMessage(int httpCode) {
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2); 
    tft.drawString("API Error", 100, 30);
    tft.drawString("HTTP Code: " + String(httpCode), 100, 60);
}

void displayMDNS() {
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setTextSize(1);
    tft.drawString("eldisplay.local", 120, tft.height() - 30); 
}

void displayNoValuesMessage() {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("To setup device", 80, 80);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("eldisplay.local", 80, 120);
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

void clearDisplay(){
    tft.fillScreen(TFT_BLACK);
}
