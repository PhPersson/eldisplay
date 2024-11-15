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
  Serial.printf("Saved %s with result: %d\n", key);
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
