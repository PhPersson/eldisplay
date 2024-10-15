#include "FileHandler.h"
#include <LittleFS.h>

// Initialize LittleFS
bool initializeFileSystem() {
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS");
    return false;
  }
  Serial.println("LittleFS mounted successfully");
  return true;
}

// Save char array to LittleFS
void saveCharToLittleFS(const char* filename, const char* value) {
  File file = LittleFS.open(filename, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  file.print(value);
  file.close();
}

// Save float to LittleFS
void saveFloatToLittleFS(const char* filename, float value) {
  File file = LittleFS.open(filename, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  file.print(String(value));
  file.close();
}

// Save bool to LittleFS
void saveBoolToLittleFS(const char* filename, bool value) {
  File file = LittleFS.open(filename, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  file.print(value ? "1" : "0");
  file.close();
}

// Load char array from LittleFS
bool loadCharFromLittleFS(const char* filename, char* buffer, size_t len) {
  File file = LittleFS.open(filename, "r");
  if (!file) {
    Serial.println(String("Error: Failed to open file for reading: ") + filename);
    return false;
  }
  file.readBytes(buffer, len);
  buffer[len - 1] = '\0';  // Ensure null-termination
  file.close();
  return true;
}


bool loadFloatFromLittleFS(const char* filename, float& value) {
  File file = LittleFS.open(filename, "r");
  if (!file) {
    Serial.println(String("Error: Failed to open file for reading: ") + filename);
    return false;
  }
  String fileContent = file.readString();
  value = fileContent.toFloat();  // Convert string to float
  file.close();
  return true;
}


// Load bool from LittleFS
bool loadBoolFromLittleFS(const char* filename, bool& value) {
  File file = LittleFS.open(filename, "r");
  if (!file) {
    Serial.println(String("Error: Failed to open file for reading: ") + filename);
    return false;
  }
  String fileContent = file.readString();
  value = (fileContent == "1");  // Return true if the file contains "1"
  file.close();
  return true;
}


// Load all settings from LittleFS and ensure default values if loading fails
bool checkValues(char* electricityPriceArea, size_t areaLen, float& priceThreshold, bool& shouldAddTax) {
  bool success = true;

  // Load the electricity price area
  if (!loadCharFromLittleFS("/electricityPriceArea.txt", electricityPriceArea, areaLen)) {
    Serial.println("Error: Using default electricity price area: SE4");
    strcpy(electricityPriceArea, "SE4");  // Default value
    success = false;
  }

  // Load the price threshold
  if (!loadFloatFromLittleFS("/priceThreshold.txt", priceThreshold)) {
    Serial.println("Error: Using default price threshold: 0.30");
    priceThreshold = 0.30;  // Default value
    success = false;
  }

  // Load the tax inclusion setting
  if (!loadBoolFromLittleFS("/shouldAddTax.txt", shouldAddTax)) {
    Serial.println("Error: Using default setting for tax inclusion: true");
    shouldAddTax = true;  // Default value
    success = false;
  }

  return success;
}