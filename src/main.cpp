#include <Arduino.h>
#include "util/seed.h"
#include "util/display.h"
#include "button/listener.h"
#include "../lib/StateMachine/src/StateMachine.h"
#include "util/menu.h"
#include "util/uitl.h"
#include "button/ButtonsHandler.h"

#define NEXT_BUTTON 12
#define PREVIOUS_BUTTON 13
#define LED 23

ButtonsHandler buttonsHandler;

void callback(byte buttonEvent) {
    Serial.println("changed");
}

void setup() {
    Serial.begin(115200);
    buttonsHandler.set(PREVIOUS_BUTTON, NEXT_BUTTON, callback);
}

void loop() {
    bool x = buttonsHandler.stateChanged(buttonsHandler.button1);
    if(x) {
        Serial.println("changed");
    }
}