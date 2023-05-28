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

#define neverPressed 0
#define onPress 1
#define onRelease 2
#define onHold 3
#define onLongPress 4

class ButtonsHandler {

public:
    struct Button {
        byte pin;

        struct {
            bool currentRawState: 1;
            bool lastRawState: 1;
            bool currentState: 1;
            bool lastState: 1;
            bool enabledLongPress: 1;
            bool wasLongPressed: 1;
            bool enableMultiHit: 1;
            unsigned long longPressSince = 0;
        } state;
    };

    Button button1;
    Button button2;
    ButtonsHandler();
    bool buttonStable(Button &button);
    void setIndividual(Button &button, byte pin);
    void set(byte pin1, byte pin2, void (*myCallback)(byte));
    void poll();
private:
    byte buttonEvent=neverPressed;
    unsigned int debounceTime = 20;

    unsigned long lastChangeTime = 0;

    void (*callback)(byte buttonEvent);

    unsigned long longPressTime = 1000;
};

#endif