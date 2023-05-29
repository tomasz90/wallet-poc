#include <Arduino.h>
#include "util/Seed.h"
#include "util/Disp.h"
#include "util/Menu.h"

#define PREVIOUS_BUTTON 13
#define NEXT_BUTTON 12
#define LED 23

Led* led = new Led(LED, 0, 20, 4);

Button previous(PREVIOUS_BUTTON, IN_PULLDOWN);
Button next(NEXT_BUTTON, IN_PULLDOWN);

ButtonsHandler buttonHandler(previous, next);

void setup() {
    Serial.begin(115200);
    Disp::begin();
    Menu::begin(led, buttonHandler);
    Seed::createMnemonic();
}

void loop() {
    Menu::run();
    buttonHandler.poll();
}
