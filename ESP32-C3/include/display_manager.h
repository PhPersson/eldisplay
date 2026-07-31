#pragma once
#include <Arduino.h>
#include <stdint.h>

void setupDisplay();
void drawCenteredPrice(float price);
void drawCenteredMessage(const String& text);
void drawConnectedMessage(const String& text);
uint16_t priceColor(float price);