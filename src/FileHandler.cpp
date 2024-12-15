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

bool loadBool(const char* key, bool& value) {
    if (preferences.isKey(key)) {
        value = preferences.getBool(key);
        return value;
    } else {
        return false;
    }
}


void removeKey(const char* key) {
  if (preferences.isKey(key)) {
      preferences.remove(key);
  }
}


String loadHTML() {
    return preferences.getString("index_html", "");
}

bool checkValues(char* priceArea, float threshold, bool nightMode){

    if (!loadChar("priceArea", priceArea, sizeof(priceArea)) || priceArea[0] == '\0') {
      return false;
    }

    if (!loadFloat("threshold", threshold) || threshold <= 0.0) {
        return false; 
    }
    nightMode = loadBool("nightMode", nightMode);

    return true;
}
