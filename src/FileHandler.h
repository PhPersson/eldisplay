#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <Arduino.h>

// Function declarations for saving variables
void saveCharToLittleFS(const char* filename, const char* value);
void saveFloatToLittleFS(const char* filename, float value);
void saveBoolToLittleFS(const char* filename, bool value);

// Function declarations for loading variables
bool loadCharFromLittleFS(const char* filename, char* buffer, size_t len);
bool loadFloatFromLittleFS(const char* filename, float& value);
bool loadBoolFromLittleFS(const char* filename, bool& value);

bool checkValues(char* electricityPriceArea, size_t areaLen, float& priceThreshold, bool& shouldAddTax);


// Initialize LittleFS
bool initializeFileSystem();

#endif // FILE_HANDLER_H
