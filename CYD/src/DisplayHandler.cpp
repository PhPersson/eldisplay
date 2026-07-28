#include "DisplayHandler.h"

TFT_eSPI tft = TFT_eSPI();
#ifndef TFT_ROTATION
#define TFT_ROTATION 1
#endif
#ifndef SCREEN_INVERTED
#define SCREEN_INVERTED false
#endif
#ifndef DISPLAY_BACKLIGHT_PIN
#define DISPLAY_BACKLIGHT_PIN 21
#endif

#define HEADER_Y 40 
#define SLOT_START_Y 80
#define SLOT_HEIGHT 45 
#define FOOTER_Y 225


void initDisplay() {
    tft.init();
    tft.setRotation(TFT_ROTATION);
    pinMode(DISPLAY_BACKLIGHT_PIN, OUTPUT);
    digitalWrite(DISPLAY_BACKLIGHT_PIN, HIGH);
    delay(1000);
    tft.fillScreen(TFT_BLACK);
    tft.invertDisplay(SCREEN_INVERTED);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
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

void displaySetupMessage(IPAddress IP) {
    drawCenteredText(tft, "Setup device at", -40, TFT_WHITE, TFT_BLACK);
    drawCenteredText(tft, "eldisplay.local", -10, TFT_YELLOW, TFT_BLACK);
    drawCenteredText(tft, "or", 20, TFT_YELLOW, TFT_BLACK);
    drawCenteredText(tft, IP.toString(), 50, TFT_YELLOW, TFT_BLACK);
}

void displayDeviceText() {
    tft.setTextSize(3);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Elpris:", tft.width() / 2, HEADER_Y);
    tft.setTextDatum(TL_DATUM);
}

void displayEnergyMessage(int startHour, int startMinute, float totalSekPerKwh, int slotsDisplayed, uint16_t textColor) {
    if (slotsDisplayed >= 3) return;
    int yPos = SLOT_START_Y + (slotsDisplayed * SLOT_HEIGHT);
    tft.fillRect(0, yPos - (SLOT_HEIGHT / 2), tft.width(), SLOT_HEIGHT, TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(textColor, TFT_BLACK);
    tft.setTextDatum(MC_DATUM); 
    char buf[32];
    snprintf(buf, sizeof(buf), "%02d:%02d      %.2f SEK", startHour, startMinute, totalSekPerKwh);
    tft.drawString(buf, tft.width() / 2, yPos);
    tft.setTextDatum(TL_DATUM);
}

void displayMDNS(IPAddress IP) {
    tft.setTextSize(1);
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(IP.toString() + " or",  tft.width() / 2, FOOTER_Y - 10);
    tft.drawString("eldisplay.local",       tft.width() / 2, FOOTER_Y);
    tft.setTextDatum(TL_DATUM);
}

void drawCenteredText(TFT_eSPI &tft, const String &message, int16_t yOffset, uint16_t textColor, uint16_t bgColor) {
    tft.setTextColor(textColor, bgColor);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(message, tft.width() / 2, tft.height() / 2 + yOffset);
    tft.setTextDatum(TL_DATUM);
}

void displayUpdateMessage() {
    clearDisplay();
    tft.setTextSize(2);
    drawCenteredText(tft, "Updating...", 0, TFT_RED, TFT_BLACK);
}
void clearDisplay() { tft.fillScreen(TFT_BLACK); }
void toggleDisplay() { digitalWrite(DISPLAY_BACKLIGHT_PIN, !digitalRead(DISPLAY_BACKLIGHT_PIN));}
void turnOnDisplay()  { digitalWrite(DISPLAY_BACKLIGHT_PIN, HIGH); }
void turnOffDisplay() { digitalWrite(DISPLAY_BACKLIGHT_PIN, LOW);  }