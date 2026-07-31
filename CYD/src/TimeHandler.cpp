#include "TimeHandler.h"


const char* getCurrentDate() {
    static char dateStr[11];

    time_t now;
    time(&now);

    struct tm timeinfo;
    localtime_r(&now, &timeinfo);

    snprintf(dateStr, sizeof(dateStr), "%04d/%02d-%02d",
             timeinfo.tm_year + 1900,
             timeinfo.tm_mon + 1,
             timeinfo.tm_mday);

    Serial.println(dateStr);
    return dateStr;
}