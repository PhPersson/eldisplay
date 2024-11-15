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
char* loadChar(const char* key, char* buffer, size_t len) {
  String value = preferences.getString(key, "");

  // Om strängen är tom eller om längden på strängen är för lång för bufferten
  if (value.length() == 0 || value.length() >= len) {
    return nullptr;  // Returnera null om något går fel
  }

  // Kopiera strängen från String till buffer
  strcpy(buffer, value.c_str());
  return buffer;  // Returnera pekaren till den laddade strängen
}

// Load float from Preferences
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
    return preferences.getString("index_html", ""); // Default to empty string if not found
}
