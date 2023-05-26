#include <Arduino.h>
#include "button.h"

Button::Button() {
    plannedMillisClick = 0;
    pendingClick = false;
}

void Button::setPending() {
    pendingClick = true;
    plannedMillisClick = millis() + 500;
}

bool Button::isPendingClick() const {
    return pendingClick;
}

bool Button::canBeClicked() const {
    long till = millis() - plannedMillisClick + 100;
    return pendingClick && till > 0;
}

void Button::setClicked() {
    pendingClick = false;
    plannedMillisClick = millis();
}



