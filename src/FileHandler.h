#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <Arduino.h>

// Function declarations for saving variables
void saveChar(const char* filename, const char* value);
void saveFloat(const char* filename, float value);
void saveBool(const char* filename, bool value);

// Function declarations for loading variables
char* loadChar(const char* filename, char* buffer, size_t len);
float loadFloat(const char* filename, float& value);
bool loadBool(const char* filename, bool& value);

String loadHTML();

bool initializePreferences();

#endif
