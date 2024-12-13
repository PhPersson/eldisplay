#include "DisplayHandler.h"
#include "user_config.h"

TFT_eSPI tft = TFT_eSPI();

void initDisplay() {
    tft.init();
    #ifdef DISPLAY_VERTICAL
        tft.setRotation(0);
    #else
        tft.setRotation(3);
    #endif
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
}

void displayConnectionFailedMessage() {
    #ifdef DISPLAY_VERTICAL
        drawCenteredText(tft, "Connect to AP:", -40, TFT_WHITE, TFT_BLACK);
        drawCenteredText(tft, "Eldisplay", 0, TFT_YELLOW, TFT_BLACK);
    #elif defined(DISPLAY_HORIZONTAL)
        drawCenteredText(tft, "Connect to AP:", -20, TFT_WHITE, TFT_BLACK);
        drawCenteredText(tft, "Eldisplay", 20, TFT_YELLOW, TFT_BLACK);
    #endif
}

void displayHttpErrorMessage(int httpCode) {
    #ifdef DISPLAY_VERTICAL
        drawCenteredText(tft, "API error", -30, TFT_YELLOW, TFT_BLACK);
        drawCenteredText(tft, "HTTP code: " + String(httpCode), 10, TFT_YELLOW, TFT_BLACK);
    #elif defined(DISPLAY_HORIZONTAL)
        drawCenteredText(tft, "API error", -20, TFT_YELLOW, TFT_BLACK);
        drawCenteredText(tft, "HTTP code: " + String(httpCode), 20, TFT_YELLOW, TFT_BLACK);
    #endif
}

void displayMDNS() {
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setTextSize(1);

    #ifdef DISPLAY_VERTICAL
        tft.drawString("eldisplay.local", (tft.width() - 120) / 2, tft.height() - 20);
    #elif defined(DISPLAY_HORIZONTAL)
        tft.drawString("eldisplay.local", (tft.width() - 80) / 2, tft.height() - 20);
    #endif
}

void displaySetupMessage() {
    #ifdef DISPLAY_VERTICAL
        drawCenteredText(tft, "Setup device at", -40, TFT_WHITE, TFT_BLACK);
        drawCenteredText(tft, "eldisplay.local", 0, TFT_YELLOW, TFT_BLACK);
    #elif defined(DISPLAY_HORIZONTAL)
        drawCenteredText(tft, "Setup device at", -20, TFT_WHITE, TFT_BLACK);
        drawCenteredText(tft, "eldisplay.local", 20, TFT_YELLOW, TFT_BLACK);
    #endif
}

void displayEnergyMessage(int startOfHour, float totalSekPerKwh, int hoursDisplayed, uint16_t textColor) {
    tft.setTextColor(textColor);
    int yPos;

    #ifdef DISPLAY_VERTICAL
        yPos = 90 + (hoursDisplayed * 60); 
    #elif defined(DISPLAY_HORIZONTAL)
        yPos = 75 + (hoursDisplayed * 40);
    #endif

    String message = String(startOfHour) + ": SEK: " + String(totalSekPerKwh, 2);
    tft.drawString(message, (tft.width() - message.length() * 12) / 2, yPos);
}

void displayDeviceText() {
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    #ifdef DISPLAY_VERTICAL
        tft.drawString("Elpris:", (tft.width() - 80) / 2, 30);
    #elif defined(DISPLAY_HORIZONTAL)
        tft.drawString("Elpris:", (tft.width() - 80) / 2, 30);
    #endif
}

void clearDisplay() {
    tft.fillScreen(TFT_BLACK);
}

void displayUpdateMessage() {
    clearDisplay();

    #ifdef DISPLAY_VERTICAL
        drawCenteredText(tft, "Updating...", 0, TFT_RED, TFT_BLACK);
    #elif defined(DISPLAY_HORIZONTAL)
        drawCenteredText(tft, "Updating...", 20, TFT_RED, TFT_BLACK);
    #endif
}

void drawCenteredText(TFT_eSPI &tft, const String &message, int16_t yOffset, uint16_t textColor, uint16_t bgColor) {
    tft.setTextColor(textColor, bgColor);

    int16_t xCenter = (tft.width() - tft.textWidth(message)) / 2;
    int16_t yCenter;

    #ifdef DISPLAY_VERTICAL
        yCenter = (tft.height() - tft.fontHeight()) / 2 + yOffset;
    #elif defined(DISPLAY_HORIZONTAL)
        yCenter = (tft.height() - tft.fontHeight()) / 2 + yOffset;
    #endif

    tft.drawString(message, xCenter, yCenter);
}


void toggleDisplay(){
    int currentState = digitalRead(21);
    digitalWrite(21, !currentState);
}

