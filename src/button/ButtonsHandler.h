/*
ButtonsHandler by cygig

ButtonsHandler is yet another Arduino library to buttonStable button (push tactile switch) and manage its events.
Events supported include pressing, releasing, holding down, long pressing (hold button for x time) and 
multi-hitting (hit button x times in y  time). For simplicity, there is only one callback function for all events, 
that passes an identifier as a parameter to indicate the event that just happened.
*/

#ifndef DAILYSTRUGGLE_H
#define DAILYSTRUGGLE_H

#if ARDUINO >= 100

#include "Arduino.h"

#else
#include "WProgram.h"
#endif

#define RELEASED 1
#define PRESSED 0

#define onPress 1
#define onRelease 2
#define onLongPress 3

class ButtonsHandler {

public:
    ButtonsHandler();
    void set(byte pin1, byte pin2, void (*myCallback)(byte));
    void poll();
private:
    struct Button {
        byte pin;

        struct {
            bool currentRawState;
            bool lastRawState;
            bool currentState;
            bool lastState;
            bool wasLongPressed;
            unsigned long longPressSince;
        } state;
    };

    Button button1;
    Button button2;

    unsigned int debounceTime = 20;
    unsigned long longPressTime = 1000;
    unsigned long lastChangeTime = 0;

    bool buttonStable(Button &button);
    static void setIndividual(Button &button, byte pin);
    void (*callback)(byte buttonEvent);
};

#endif