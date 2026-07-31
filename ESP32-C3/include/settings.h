#pragma once
#include "Arduino.h"
void loadSettings();
void saveSettings(const String& area, bool tax, float thresh);