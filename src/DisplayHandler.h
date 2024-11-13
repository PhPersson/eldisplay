// #include <Adafruit_ILI9341.h>
#include <TFT_eSPI.h>

// extern Adafruit_ILI9341 tft;
// extern TFT_eSPI tft;

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