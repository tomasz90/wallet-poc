#include <Arduino.h>

#include <utility>
#include "button.h"

OldButton::OldButton(std::string name) {
    this->name = std::move(name);
    plannedMillisClick = 0;
    pendingClick = false;
}

void OldButton::setPending() {
    pendingClick = true;
    plannedMillisClick = millis() + 200;
}

bool OldButton::isPendingClick() const {
    return pendingClick;
}

bool OldButton::canBeClicked() const {
    long till = millis() - plannedMillisClick;
    return pendingClick && till > 0;
}

void OldButton::setClicked() {
    pendingClick = false;
    plannedMillisClick = millis();
}

std::string OldButton::getName() {
    return name;
}



