//
// Created by Tomasz Kulig on 26/05/2023.
//
#include <Arduino.h>
#include "button.h"

Button::Button() {
    plannedMillisClick = 0;
    pendingClick = false;
}

void Button::setPending() {
    pendingClick = true;
    plannedMillisClick = millis() + 300;
}

// for both
bool Button::isPendingClick() const {
    return pendingClick;
}

// for one
bool Button::canBeClicked() const {
    long till = millis() - plannedMillisClick;
    return pendingClick && till > 0;
}

void Button::setClicked() {
    pendingClick = false;
    plannedMillisClick = millis();
}



