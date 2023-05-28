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

    s.enableLongPress = false;
    s.wasLongPressed = false;
    s.enableMultiHit = false;
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

bool ButtonsHandler::poll() {
    // Straight away end poll if debounce fails
    if (buttonStable(button1) == 0) { return 0; }
    auto &s = button1.state;
    ;
    /*======================================*/
    /* FIRST Scenario,PRESSED after PRESSED */
    /*======================================*/
    if (s.currentState == PRESSED && s.lastState == PRESSED) { //2I
        // enableLongPress 1st Check: Is it enabled?
        if (s.enableLongPress) { //3I

            // enableLongPress 2nd Check: Was the button held down long enough?
            if ((unsigned long) (millis() - s.longPressSince) >= longPressTime) { //4I
                //reset timing for the next onLongPress
                s.longPressSince = millis();

                // You need this so the next onRelease will not trigger when user let go of the button
                s.wasLongPressed = true;

            } //4I

        } //3I

    } //2I

        /*=========================================*/
        /* SECOND Scenario, PRESSED after RELEASED */
        /*=========================================*/
    else if (s.currentState == PRESSED && s.lastState == RELEASED) { //2EI

        //Trigger onPress event
        s.longPressSince = millis(); // Reset since it was previously released
        buttonEvent = onPress;
        callback(buttonEvent);

    } //2EI

        /*========================================*/
        /* THIRD Scenario, RELEASED after PRESSED */
        /*========================================*/
    else if (s.currentState == RELEASED && s.lastState == PRESSED) { //2EI

        if (s.wasLongPressed) { //3I
            s.wasLongPressed = false;
            // Do nothing here as we do not want to register
            // the onRelease right after a longPressFor
        } //3I

        else { //3E

            // Trigger onRelease event
            buttonEvent = onRelease;
            callback(buttonEvent);
        } //3E

    } //2EI

    // Record the current button state
    s.lastState = s.currentState;
    return 1;
}
