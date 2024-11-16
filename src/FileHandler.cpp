#include "FileHandler.h"
#include <Preferences.h>

Preferences preferences;

// Initialize Preferences
bool initializePreferences() {
  preferences.begin("settings", false);
  Serial.println("Preferences initialized successfully");
  return true;
}

void saveChar(const char* key, const char* value) {
  preferences.putString(key, value);
  Serial.printf("Saved %s with result: %d\n", key);
}


void saveFloat(const char* key, float value) {
  preferences.putFloat(key, value);
}

void saveBool(const char* key, bool value) {
  preferences.putBool(key, value);
}


char* loadChar(const char* key, char* buffer, size_t len) {
  String value = preferences.getString(key, "");
  if (value.length() == 0 || value.length() >= len) {
    return nullptr;
  }
  strcpy(buffer, value.c_str());
  return buffer;
}


float loadFloat(const char* key, float& value) {
  value = preferences.getFloat(key, 0.0);
  return value;
}

// Load bool from Preferences
bool loadBool(const char* key, bool& value) {
  value = preferences.getBool(key, true);
  return true;
}

String loadHTML() {
    return preferences.getString("index_html", "");
}

bool checkValues(bool addTax, char* priceArea, float threshold){


    Serial.println(loadChar("priceArea", priceArea, sizeof(priceArea)) || priceArea[0] == '\0');
    Serial.println(loadFloat("threshold", threshold) || threshold <= 0.0);
    Serial.println(loadBool("addTax", addTax));
    if (!loadChar("priceArea", priceArea, sizeof(priceArea)) || priceArea[0] == '\0') {
      return false;
    }

    if (!loadFloat("threshold", threshold) || threshold <= 0.0) {
        return false; 
    }

    if (!loadBool("addTax", addTax)) {
        return false;
    }

    return true;
}
