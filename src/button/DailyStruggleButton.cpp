#include "DailyStruggleButton.h"

// Empty Constructor, we will use setup() instead;
DailyStruggleButton::DailyStruggleButton() {}

bool DailyStruggleButton::debounce() {

    flags.currentRawState = digitalRead(pin);
    // If the button state did not change within debounce time,
    // then we considered it stable
    if (flags.currentRawState == flags.lastRawState) {
        bool moreThanDebounceTime = (unsigned long) (millis() - lastChangeTime) >= debounceTime;
        if (moreThanDebounceTime) {
            flags.currentState = flags.currentRawState;
        }
        return moreThanDebounceTime;
    } else {
        // However if it keeps changing, we keep resetting the debounce timer
        lastChangeTime = millis();
        flags.lastRawState = flags.currentRawState;
        return false;
    }
}
