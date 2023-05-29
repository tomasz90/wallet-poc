#include <Arduino.h>
#include "util/seed.h"
#include "util/display.h"
#include "button/listener.h"
#include "../lib/StateMachine/src/StateMachine.h"
#include "util/menu.h"
#include "util/uitl.h"
#include "buttons/Button.h"
#include "buttons/ButtonsHandler.h"

#define PREVIOUS_BUTTON 13
#define NEXT_BUTTON 12
#define LED 23

Button previous(PREVIOUS_BUTTON, IN_PULLDOWN);
Button next(NEXT_BUTTON, IN_PULLDOWN);
ButtonsHandler buttonHandler(previous, next);

void onPrevious() {
    Menu::previousCalled = true;
}
void onNext() {
    Menu::nextCalled = true;
}
void onBoth() {
    Menu::bothCalled = true;
}

void setup() {
    Serial.begin(115200);
    Util::initDisplay();
    Seed::createMnemonic();
    buttonHandler.setCallbacks(onPrevious, onNext, onBoth);
    Menu::begin();
}

void loop() {
    Menu::run();
    buttonHandler.poll();
}
