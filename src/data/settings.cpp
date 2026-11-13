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
  showOnlyCurrentPrice = prefs.getBool("showOnlyCurrentPrice", false);
  prefs.end();
}

void saveSettings(const String& area, bool tax, float thresh, bool shouldShowOnlyCurrentPrice) {
  prefs.begin("elpris", false);
  prefs.putString("area", area);
  prefs.putBool("tax", tax);
  prefs.putFloat("thresh", thresh);
  prefs.putBool("showOnlyCurrentPrice", shouldShowOnlyCurrentPrice);
  prefs.end();

  priceArea = area;
  addTax = tax;
  threshold = thresh;
  showOnlyCurrentPrice = shouldShowOnlyCurrentPrice;
}