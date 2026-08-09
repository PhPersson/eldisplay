#include "time_manager.h"
#include "app_state.h"

void setupTime() {
  configTime(0, 0, "pool.ntp.org");
  setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
  tzset();

  struct tm timeinfo;
  int retries = 0;
  while (!getLocalTime(&timeinfo, 1000) && retries < 20) {
    delay(500);
    retries++;
  }
}
String todayPath() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo, 1000)) {
    return "";
  }

  char buf[64];
  strftime(buf, sizeof(buf), "/api/v1/prices/%Y/%m-%d_", &timeinfo);
  return String(buf) + priceArea + ".json?unit=kr";
}