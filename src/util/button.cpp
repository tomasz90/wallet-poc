//
// Created by Tomasz Kulig on 26/05/2023.
//
#include <Arduino.h>
#include "button.h"

Button::Button() {
    plannedMillisClick = 0;
    pendingClick = false;
}

bool Button::isActive() {
    return !pendingClick && millis() - plannedMillisClick > 200;
}

void Button::setPending() {
    pendingClick = true;
    plannedMillisClick = millis() + 500;
}

// for both
bool Button::isPendingClick() {
    return pendingClick;
}

// for one
bool Button::canBeClicked() {
    long till = millis() - plannedMillisClick;
    return pendingClick && till > 0;
}

void Button::setClicked() {
    pendingClick = false;
    plannedMillisClick = millis();
}



