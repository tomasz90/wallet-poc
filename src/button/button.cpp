#include <Arduino.h>

#include <utility>
#include "button.h"

Button::Button(std::string name) {
    this->name = std::move(name);
    plannedMillisClick = 0;
    pendingClick = false;
}

void Button::setPending() {
    pendingClick = true;
    plannedMillisClick = millis() + 250;
}

bool Button::isPendingClick() const {
    return pendingClick;
}

bool Button::canBeClicked() const {
    long till = millis() - plannedMillisClick;
    return pendingClick && till > 0;
}

void Button::setClicked() {
    pendingClick = false;
    plannedMillisClick = millis();
}

std::string Button::getName() {
    return name;
}



