#include <Arduino.h>
#include "util/seed.h"
#include "util/display.h"
#include "util/menu.h"
#include "util/uitl.h"

#define PREVIOUS_BUTTON 13
#define NEXT_BUTTON 12
#define LED 23

Led* led = new Led(LED, 0, 20, 4);

Button previous(PREVIOUS_BUTTON, IN_PULLDOWN);
Button next(NEXT_BUTTON, IN_PULLDOWN);

ButtonsHandler buttonHandler(previous, next);

void setup() {
    Serial.begin(115200);
    Util::initDisplay();
    Menu::begin(led, buttonHandler);
    Seed::createMnemonic();
}

void loop() {
    Menu::run();
    buttonHandler.poll();
}
