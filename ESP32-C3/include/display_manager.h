#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <LovyanGFX.hpp>

void setupDisplay();
void drawCenteredPrice(float price, float threshold);
void drawUpcomingPrices(float currentPrice, float upcomingPrice1, float upcomingPrice2, float threshold);
void drawCenteredMessage(const String& text);
void drawConnectedMessage(const String& text);
uint16_t priceColor(float price,float threshold);
void drawHeader(const String &text, uint16_t color);

void displayConnectionFailedMessage();