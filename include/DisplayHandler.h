#include <TFT_eSPI.h>


void initDisplay();

void displayConnectionFailedMessage();

void displayHttpErrorMessage(int httpCode);

void displayMDNS(IPAddress IP);

void displaySetupMessage(IPAddress IP);

void displayEnergyMessage(int startOfHour, float totalSekPerKwh, int hoursDisplayed, uint16_t textColor);

void displayDeviceText();

void clearDisplay();

void displayUpdateMessage();

void drawCenteredText(TFT_eSPI &tft, const String &message, int16_t yOffset, uint16_t textColor, uint16_t bgColor);

void toggleDisplay();

void turnOnDisplay();

void turnOffDisplay();
