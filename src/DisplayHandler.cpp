#include "DisplayHandler.h"
#include "user_config.h"

TFT_eSPI tft = TFT_eSPI();

void initDisplay() {
    tft.init();
    tft.setRotation(0);
    pinMode(10, OUTPUT);  // Ställ in GPIO10 som en utgång
    digitalWrite(10, HIGH);  // Sätt GPIO10 till HIGH
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
}

void displayConnectionFailedMessage() {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Connect to AP:", (tft.width() - 120) / 2, tft.height() / 2 - 40);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("Eldisplay", (tft.width() - 80) / 2, tft.height() / 2);
}

void displayHttpErrorMessage(int httpCode) {
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2); 
    tft.drawString("API Error", (tft.width() - 90) / 2, tft.height() / 2 - 60);
    tft.drawString("HTTP Code: " + String(httpCode), (tft.width() - 140) / 2, tft.height() / 2 - 20);
}

void displayMDNS() {
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setTextSize(1);
    tft.drawString("eldisplay.local", (tft.width() - 120) / 2, tft.height() - 20);
}

void displayNoValuesMessage() {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.drawString("To setup device", (tft.width() - 120) / 2, tft.height() / 2 - 20);  // Fasta positioner för första raden
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("eldisplay.local", (tft.width() - 120) / 2, tft.height() / 2 + 20);  // Fasta positioner för andra raden
}


void displayEnergyMessage(int startOfHour, float totalSekPerKwh, int hoursDisplayed, uint16_t textColor) {
    tft.setTextColor(textColor);
    int yPos = 80 + (hoursDisplayed * 50); 
    String message = String(startOfHour) + ": SEK: " + String(totalSekPerKwh, 2);
    tft.drawString(message, (tft.width() - message.length() * 12) / 2, yPos);
}

void displayDeviceText() {
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Elpris:", (tft.width() - 80) / 2, 30);
}

void clearDisplay() {
    tft.fillScreen(TFT_BLACK);
}

void displayUpdateMessage() {
    clearDisplay();
    tft.setTextSize(2);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("Updating...", (tft.width() - 140) / 2, tft.height() / 2 - 10);
}
