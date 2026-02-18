#include "DisplayHandler.h"

TFT_eSPI tft = TFT_eSPI();

void initDisplay() {
    tft.init();
    tft.setRotation(0);
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH); 
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
}

void displayConnectionFailedMessage() {
    drawCenteredText(tft, "Connect to AP:", -20, TFT_WHITE, TFT_BLACK);
    drawCenteredText(tft, "Eldisplay", 20, TFT_YELLOW, TFT_BLACK);
}

void displayHttpErrorMessage(int httpCode) {
    tft.setTextSize(2); 
    drawCenteredText(tft, "API Error", -20, TFT_YELLOW, TFT_BLACK);
    drawCenteredText(tft, "HTTP Code: " + String(httpCode), 20, TFT_YELLOW, TFT_BLACK);
}

void displayMDNS(IPAddress IP) {
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setTextSize(1);
    tft.drawString(IP.toString() + " or", (tft.width() - 120) / 2 + 20, tft.height() - 30);
    tft.drawString("eldisplay.local", (tft.width() - 120) / 2 + 20, tft.height() - 20);
}

void displaySetupMessage(IPAddress IP) {
    drawCenteredText(tft, "Setup device at", -20, TFT_WHITE, TFT_BLACK);
    drawCenteredText(tft, "eldisplay.local", 20, TFT_YELLOW, TFT_BLACK);
    drawCenteredText(tft, "or", 40, TFT_YELLOW, TFT_BLACK);
    drawCenteredText(tft, IP.toString(), 60, TFT_YELLOW, TFT_BLACK);
}


void displayEnergyMessage(int startOfHour, float totalSekPerKwh, int hoursDisplayed, uint16_t textColor) {
    tft.setTextColor(textColor);
    int yPos = 80 + (hoursDisplayed * 50 + 10); 
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
    drawCenteredText(tft, "Updating...", 0, TFT_RED, TFT_BLACK);
}


void drawCenteredText(TFT_eSPI &tft, const String &message, int16_t yOffset, uint16_t textColor, uint16_t bgColor) {
    tft.setTextColor(textColor, bgColor);

    int16_t xCenter = (tft.width() - tft.textWidth(message)) / 2;
    int16_t yCenter = (tft.height() - tft.fontHeight()) / 2 + yOffset;

    tft.drawString(message, xCenter, yCenter);
}


void toggleDisplay(){
    int currentState = digitalRead(10);
    digitalWrite(10, !currentState);
}

void turnOnDisplay(){
    digitalWrite(10, HIGH);
}

void turnOffDisplay(){
    digitalWrite(10, LOW);
}