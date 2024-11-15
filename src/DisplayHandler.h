#include <TFT_eSPI.h>


void initDisplay();

void displayConnectedMessage();

void displayConnectionFailedMessage();

void displayHttpErrorMessage(int httpCode);

void displayMDNS();

void displayNoValuesMessage();

void displayEnergyMessage(int startOfHour, float totalSekPerKwh, int hoursDisplayed, uint16_t textColor);

void displayDeviceText();

void displayJsonError(const String& error);

void clearDisplay();