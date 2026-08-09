#include "display_manager.h"
#include "LGFX_ESP32_S3_LCD_2.hpp"
#include "LGFX_ESP32_CYD.hpp"
#include "LGFX_ESP32_GC9A01.hpp"

#if defined(BOARD_ESP32_GC9A01_ROUND)
static LGFX_ESP32_GC9A01 lcd;
#elif defined(BOARD_ESP32_LCD2_ST7789)
static LGFX_ESP32_S3_LCD_2 lcd;
#elif defined(BOARD_ESP32_CYD)
static LGFX_ESP32_CYD lcd;
#endif


void setupDisplay() {
  lcd.init();
  #if defined(BOARD_ESP32_GC9A01_ROUND)
  lcd.setRotation(0);
  #elif defined(BOARD_ESP32_LCD2_ST7789)
  lcd.setRotation(1);
  #elif defined(BOARD_ESP32_CYD)
  lcd.setRotation(6);
  lcd.invertDisplay(true);
  #endif
  lcd.setBrightness(180);

}
void drawHeader(const String &text, uint16_t color = TFT_WHITE) {
    lcd.setTextSize(1);
    lcd.setTextColor(color, TFT_BLACK);
    lcd.setTextDatum(TC_DATUM);
    int headerY = 22;
    lcd.drawString(text, lcd.width() / 2, headerY);

    lcd.setTextDatum(TL_DATUM);
}

uint16_t priceColor(float price, float threshold) {
  return price > threshold ? TFT_RED : TFT_GREEN;
}

void drawCenteredPrice(float price, float threshold) {
  
  lcd.fillScreen(TFT_BLACK);
  drawHeader("Elpriset",TFT_WHITE);
  lcd.setFont(&fonts::Font8);
  lcd.setTextColor(priceColor(price, threshold), TFT_BLACK);

  String text = String(price, 2);
  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 95;

  lcd.setCursor(x, y);
  lcd.print(text);
}

void drawCenteredMessage(const String& text) {
  lcd.fillScreen(TFT_BLACK);
  lcd.setFont(&fonts::Font4);
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);

  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 110;

  lcd.setCursor(x, y);
  lcd.print(text);
}

void drawConnectedMessage(const String& text) {
  lcd.fillScreen(TFT_BLACK);
  lcd.setFont(&fonts::Font4);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);

  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 110;

  lcd.setCursor(x, y);
  lcd.print(text);
}


void displayConnectionFailedMessage() {
  lcd.fillScreen(TFT_BLACK);
  lcd.setFont(&fonts::Font4);
  lcd.setTextColor(TFT_RED, TFT_BLACK);

  String text = "Connect to AP Eldisplay";
  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 110;

  lcd.setCursor(x, y);
  lcd.print(text);
}

void drawUpcomingPrices(
    float currentPrice,
    float upcomingPrice1,
    float upcomingPrice2,
    float threshold
) {
    char priceText[32];

    lcd.fillScreen(TFT_BLACK);
    drawHeader("Elpriset", TFT_WHITE);

    lcd.setFont(&fonts::Font4);
    lcd.setTextDatum(middle_center);

    const int centerX = lcd.width() / 2;

    snprintf(
        priceText,
        sizeof(priceText),
        "Nu: %.2f SEK",
        currentPrice
    );

    lcd.setTextColor(
        priceColor(currentPrice, threshold),
        TFT_BLACK
    );

    lcd.drawString(priceText, centerX, 65);

    snprintf(
        priceText,
        sizeof(priceText),
        "15 min: %.2f SEK",
        upcomingPrice1
    );

    lcd.setTextColor(
        priceColor(upcomingPrice1, threshold),
        TFT_BLACK
    );

    lcd.drawString(priceText, centerX, 115);

    snprintf(
        priceText,
        sizeof(priceText),
        "30 min: %.2f SEK",
        upcomingPrice2
    );

    lcd.setTextColor(
        priceColor(upcomingPrice2, threshold),
        TFT_BLACK
    );

    lcd.drawString(priceText, centerX, 165);

    lcd.setTextDatum(top_left);
}