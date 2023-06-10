#include "Flag.h"

bool Flag::check() {
    bool temp = flag;
    if (flag) {
        flag = false;
    }
    return temp;
}

void Flag::set() { flag = true; }

void Flag::unset() { flag = false; }