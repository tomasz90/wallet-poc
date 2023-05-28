#include "ButtonsHandler.h"

// Empty Constructor, we will use setup() instead;
ButtonsHandler::ButtonsHandler() {}

void ButtonsHandler::set(byte pin1, byte pin2, void (*myCallback)(byte buttonEvent)) {
    setIndividual(button1, pin1);
    setIndividual(button2, pin2);
    callback = myCallback;
}

void ButtonsHandler::setIndividual(Button &button, byte pin) {
    button.pin = pin;
    pinMode(button.pin, INPUT_PULLUP);
    auto &s = button.state;
    s.currentRawState = RELEASED;
    s.lastRawState = RELEASED;
    s.currentState = RELEASED;
    s.lastState = RELEASED;

    s.wasLongPressed = false;
    s.longPressSince = 0;
}

// Only currentState used outside this function
bool ButtonsHandler::buttonStable(Button &button) {

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

void ButtonsHandler::poll() {
    if (buttonStable(button1) == 0) { return; }

    auto &s = button1.state;

    /*================================*/
    /* ON_LONG: PRESSED after PRESSED */
    /*================================*/
    if (s.currentState == PRESSED && s.lastState == PRESSED) {
        // Was the button held down long enough?
        if ((unsigned long) (millis() - s.longPressSince) >= longPressTime) {
            // Reset timing for the next onLongPress
            s.longPressSince = millis();
            // You need this so the next onRelease will not trigger when user let go of the button
            s.wasLongPressed = true;
            callback(onLongPress);
        }
    }
    /*=========================================*/
    /* PRESS: PRESSED after RELEASED */
    /*=========================================*/
    else if (s.currentState == PRESSED && s.lastState == RELEASED) {
        // Reset since it was previously released
        s.longPressSince = millis();
        callback(onPress);
    }
    /*========================================*/
    /* RELEASED: RELEASED after PRESSED */
    /*========================================*/
    else if (s.currentState == RELEASED && s.lastState == PRESSED) {
        if (s.wasLongPressed) {
            s.wasLongPressed = false;
            // Do nothing here as we do not want to register
            // the onRelease right after a longPressFor
        } else {
            callback(onRelease);
        }
    }
    // Record the current button state
    s.lastState = s.currentState;
}
