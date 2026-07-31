#include "settings.h"
#include "app_state.h"
#include "Arduino.h"
#include <Preferences.h>
static Preferences prefs;

void loadSettings() {
  prefs.begin("elpris", true);
  priceArea = prefs.getString("area", "SE4");
  addTax = prefs.getBool("tax", false);
  threshold = prefs.getFloat("thresh", 1.0f);
  prefs.end();
}

void saveSettings(const String& area, bool tax, float thresh) {
  prefs.begin("elpris", false);
  prefs.putString("area", area);
  prefs.putBool("tax", tax);
  prefs.putFloat("thresh", thresh);
  prefs.end();

  priceArea = area;
  addTax = tax;
  threshold = thresh;
}