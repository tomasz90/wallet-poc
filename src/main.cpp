#include <Arduino.h>
#include "util/seed.h"
#include "util/display.h"
#include "util/interuptive.h"
#include "../lib/StateMachine/src/StateMachine.h"
#include "util/menu.h"
#include "util/uitl.h"

#define NEXT_BUTTON 12
#define PREVIOUS_BUTTON 0
#define LED 23

void setup() {
    Serial.begin(115200);
    Util::initDisplay();
    Seed::createMnemonic();
    Interaptive::begin(PREVIOUS_BUTTON, NEXT_BUTTON, LED);
    Menu::begin();
}

void loop() {
    Menu::run();
}
