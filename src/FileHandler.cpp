#include "FileHandler.h"
#include <Preferences.h>


Preferences preferences;

// Initialize Preferences
bool initializePreferences() {
  preferences.begin("settings", false);
  Serial.println("Preferences initialized successfully");
  return true;
}

// Save char array to Preferences
void saveChar(const char* key, const char* value) {
  preferences.putString(key, value);
}

// Save float to Preferences
void saveFloat(const char* key, float value) {
  preferences.putFloat(key, value);
}

// Save bool to Preferences
void saveBool(const char* key, bool value) {
  preferences.putBool(key, value);
}

// Load char array from Preferences
bool loadChar(const char* key, char* buffer, size_t len) {
  String value = preferences.getString(key, "");
  if (value.length() >= len) {
    return false;
  }
  strcpy(buffer, value.c_str());
  return true;
}

// Load float from Preferences
bool loadFloat(const char* key, float& value) {
  value = preferences.getFloat(key, 0.0);
  return true;
}

// Load bool from Preferences
bool loadBool(const char* key, bool& value) {
  value = preferences.getBool(key, true);
  return true;
}

String loadHTML() {
    return preferences.getString("index_html", ""); // Default to empty string if not found
}

// // Load all settings from Preferences and ensure default values if loading fails
// bool checkValues(char* electricityPriceArea, size_t areaLen, float& priceThreshold, bool& shouldAddTax) {
//   bool success = true;

//   if (!loadCharFromPreferences("electricityPriceArea", electricityPriceArea, areaLen)) {
//     Serial.println("Error: Using default electricity price area: SE4");
//     strcpy(electricityPriceArea, "SE4"); 
//     success = false;
//   }

//   // Load the price threshold
//   if (!loadFloatFromPreferences("priceThreshold", priceThreshold)) {
//     Serial.println("Error: Using default price threshold: 0.30");
//     priceThreshold = 0.30;  // Default value
//     success = false;
//   }

//   // Load the tax inclusion setting
//   if (!loadBoolFromPreferences("shouldAddTax", shouldAddTax)) {
//     Serial.println("Error: Using default setting for tax inclusion: true");
//     shouldAddTax = true;  // Default value
//     success = false;
//   }

//   return success;
// }

// Factory reset function
void factoryReset() {
  preferences.clear();
  Serial.println("Preferences have been reset");
}
