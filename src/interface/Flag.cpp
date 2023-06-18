#include <HardwareSerial.h>
#include "Flag.h"

bool Flag::check() {
    bool temp = flag;
    if (flag) {
        flag = false;
    }
    return temp;
}

void Flag::set() {
    flag = true;
}

void Flag::unset() {
    flag = false;
}

bool DoubleFlag::check() {
    bool temp = a.flag && b.flag;
    if (temp) {
        a.flag = false;
        b.flag = false;
    }
    return temp;
}

bool MixedFlag::check() {
    bool temp = a.flag && inverted != b;
    if (temp) {
        a.flag = false;
    }
    return temp;
}