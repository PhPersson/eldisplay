#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;

void initDisplay();

void displayConnectedMessage();

void displayConnectionFailedMessage();

void displayHttpErrorMessage(int httpCode);

void displayMDNS();

void displayNoValuesMessage();

void displayMessageCenter(String message);

void displayEnergyMessage(int startOfHour, float totalSekPerKwh, int hoursDisplayed, uint16_t textColor);

void displayDeviceText();