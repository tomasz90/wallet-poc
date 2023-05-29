#include <Arduino.h>
#include "util/seed.h"
#include "util/display.h"
#include "../lib/StateMachine/src/StateMachine.h"
#include "util/menu.h"
#include "util/uitl.h"
#include "util/Led.h"
#include "button.h"
#include "ButtonsHandler.h"

#define PREVIOUS_BUTTON 13
#define NEXT_BUTTON 12
#define LED 23

Button previous(PREVIOUS_BUTTON, IN_PULLDOWN);
Button next(NEXT_BUTTON, IN_PULLDOWN);
ButtonsHandler buttonHandler(previous, next);

Led led(LED, 0, 20, 4);

void onPrevious() {
    led.flash();
    Menu::previousCalled = true;
}
void onNext() {
    led.flash();
    Menu::nextCalled = true;
}
void onBoth() {
    led.flash();
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
