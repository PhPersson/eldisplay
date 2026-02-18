#include <Utils.h>

void disableLED(){
    pinMode(15, OUTPUT);
    digitalWrite(15, LOW);
}