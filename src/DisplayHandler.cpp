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
    tft.setCursor(10, 10); // Start at the top left
}


void displayConnectedMessage(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_GREEN);
    tft.println("Connected to WiFi");
}

void displayConnectionFailedMessage(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(20, 10);
    tft.setTextColor(ILI9341_RED);
    tft.println("Connect to AP:");
    tft.setCursor(20, 50);
    tft.setTextColor(ILI9341_YELLOW);
    tft.println("Eldisplay");
}

void displayHttpErrorMessage(int httpCode){
    tft.fillScreen(ILI9341_BLACK);
    Serial.print("Error on HTTP request: ");
    Serial.println(httpCode);
    tft.setCursor(10, 60);
    tft.setTextColor(ILI9341_RED);
    tft.println("Error when requesting API");
}

void displayMDNS(){
    tft.setTextColor(ILI9341_WHITE); // Sets text color to white
    tft.setTextSize(1); // Text size
    tft.setCursor(80, tft.height() - 30);  // Adjust the x position as needed for centering
    tft.print("eldisplay.local");
}


void displayNoValuesMessage(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(35, 60);
    tft.setTextColor(ILI9341_WHITE);
    tft.println("To setup device");
    tft.setCursor(35, 90);
    tft.println("eldisplay.local");
}


void displayMessageCenter(String message){
    tft.setTextColor(ILI9341_WHITE); // Sets text color to white
    tft.setTextSize(2); // Text size
    
    // Calculate the width of the message in pixels
    int16_t textWidth = message.length() * 6 * 2;  // 6 is the width of a character in the default font, '2' is the text size multiplier
    
    // Set the cursor to center horizontally
    int16_t xPos = (tft.width() - textWidth) / 2;
    int16_t yPos = (tft.height() - 16 * 2) / 2;  // 16 is the height of a character in the default font, '2' is the text size multiplier
    
    // Set cursor to the calculated position
    tft.setCursor(xPos, yPos);
    
    // Print the message
    tft.print(message);
}