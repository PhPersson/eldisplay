#include <Utils.h>

void disableLED(){
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
}


