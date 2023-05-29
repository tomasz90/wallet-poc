#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define RELEASED 0
#define PRESSED 1

enum Mode {
    IN_PULLUP = INPUT_PULLUP,
    IN_PULLDOWN = INPUT_PULLDOWN,
};

struct Button {
    byte pin;
    Mode mode;
    bool invertedState;
    struct {
        bool lastRawState;
        bool currentState;
        bool lastState;
        unsigned long lastChangeTime;
    } state;

    Button(byte buttonPin, Mode buttonMode) : pin(buttonPin), mode(buttonMode) {
        switch (mode) {
            case IN_PULLUP:
                invertedState = true;
                break;
            case IN_PULLDOWN:
                invertedState = false;
        }
        pinMode(pin, mode);
        state.lastRawState = RELEASED;
        state.currentState = RELEASED;
        state.lastState = RELEASED;
        state.lastChangeTime = 0;
    }
};


#endif //BUTTON_H
