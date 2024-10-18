#include "DisplayHandler.h"
#include "user_config.h"


// Initialize the ILI9341 display 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void initDisplay(){
    tft.begin();
    tft.setRotation(0); // Horizontal mode on the screen
    tft.fillScreen(ILI9341_BLACK); // Clears the screen before displaying new text
    tft.setTextColor(ILI9341_WHITE); // Sets text color to white
    tft.setTextSize(2); // Text size
}


void displayConnectedMessage(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 60);
    tft.setTextColor(ILI9341_GREEN);
    tft.println("Connected to WiFi");
}

void displayConnectionFailedMessage(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 60);
    tft.printf("Connect to AP:");
    tft.setCursor(10, 90);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Eldisplay");
}

void displayHttpErrorMessage(int httpCode){
    tft.setTextColor(ILI9341_RED);
    tft.setTextSize(2);  // Increase the text size for better visibility
    
    tft.setCursor(10, 60);
    tft.println("API Request Error");
    
    // Display the HTTP error code
    tft.setCursor(10, 90);
    tft.print("HTTP Code: ");
    tft.println(httpCode);
}

void displayMDNS(){
    tft.setTextColor(ILI9341_WHITE); // Sets text color to white
    tft.setTextSize(1); // Text size
    tft.setCursor(80, tft.height() - 30);  // Adjust the x position as needed for centering
    tft.setTextColor(ILI9341_LIGHTGREY);
    tft.print("eldisplay.local");
}


void displayNoValuesMessage(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 60);
    tft.setTextColor(ILI9341_WHITE);
    tft.printf("To setup device\n");
    tft.setCursor(10, 90);
    tft.setTextColor(ILI9341_YELLOW);
    tft.printf("eldisplay.local\n");

}


void displayMessageCenter(String message){}

void displayEnergyMessage(int startOfHour, float totalSekPerKwh, int hoursDisplayed, uint16_t textColor) {

    tft.setTextColor(textColor);
    // Calculate the Y position dynamically
    int yPos = 80 + (hoursDisplayed * 40);

    tft.setCursor(40, yPos);
    tft.printf("%02d: SEK: %.2f", startOfHour, totalSekPerKwh);
}


void displayDeviceText(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setCursor(80, 30);
    tft.setTextColor(ILI9341_WHITE);
    tft.println("Elpris:");
}


void displayJsonError(const String& error) {

    Serial.print("Failed to parse JSON: ");
    Serial.println(error);
    
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_RED); 
    tft.setTextSize(2);

    tft.setCursor(10, 60);
    tft.println("Error from API:");

    tft.setCursor(10, 90);
    tft.println(error);
}