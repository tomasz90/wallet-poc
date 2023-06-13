#include <HardwareSerial.h>
#include "Flag.h"

bool Flag::check() {
    bool temp = flag;
    if (flag) {
        Serial.println("One flag was triggered.");
        flag = false;
    }
    return temp;
}

void Flag::set() {
    Serial.println("Flag was set.");
    flag = true;
}

void Flag::unset() {
    Serial.println("Flag was unset.");
    flag = false;
}

bool DoubleFlag::check() {
    bool temp = a.flag && b.flag;
    Serial.println("Checking double flag. a: " + String(a.flag) + ", b: " + String(b.flag));
    if (temp) {
        Serial.println("Two flags were triggered.");
        a.flag = false;
        b.flag = false;
    }
    return temp;
}