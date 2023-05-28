#include "ButtonsHandler.h"

// Empty Constructor, we will use setup() instead;
ButtonsHandler::ButtonsHandler() {}

void ButtonsHandler::set(byte pin1, byte pin2, void (*myCallback)(byte buttonEvent)) {
    setIndividual(button1, pin1);
    setIndividual(button2, pin2);
    callback = myCallback;
}

void ButtonsHandler::setIndividual(Button &button, byte pin) {
    pinMode(pin, INPUT_PULLUP);
    button.pin = pin;
    auto &s = button.state;
    s.currentRawState = RELEASED;
    s.lastRawState = RELEASED;
    s.currentState = RELEASED;
    s.lastState = RELEASED;

    s.enableLongPress = false;
    s.wasLongPressed = false;
    s.enableMultiHit = false;
}

// Only currentState used outside this function
bool ButtonsHandler::stateChanged(Button &button) {

    button.state.currentRawState = digitalRead(button.pin);
    // If the button state did not change within stateChanged time,
    // then we considered it stable
    if (button.state.currentRawState == button.state.lastRawState) {
        bool moreThanDebounceTime = (unsigned long) (millis() - lastChangeTime) >= debounceTime;
        if (moreThanDebounceTime) {
            button.state.currentState = button.state.currentRawState;
            return true;
        }
    } else {
        // However if it keeps changing, we keep resetting the stateChanged timer
        lastChangeTime = millis();
        button.state.lastRawState = button.state.currentRawState;
    }
    return false;
}
