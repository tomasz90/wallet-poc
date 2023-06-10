#include <Arduino.h>
#include "util/SeedGenerator.h"
#include "interface/Disp.h"
#include "interface/Menu.h"
#include "util/Nav.h"
#include "util/Pin.h"
#include "io/Bluetooth.h"

#define PREVIOUS_BUTTON 2
#define NEXT_BUTTON 25
#define LED 23

Led* led = new Led(LED, 0, 20, 4);

Button previous(PREVIOUS_BUTTON, IN_PULLDOWN);
Button next(NEXT_BUTTON, IN_PULLDOWN);

ButtonsHandler buttonHandler(previous, next);

void setup() {
    Serial.begin(115200);
    auto disp = new Disp();
    auto seedGenerator = new SeedGenerator();
    auto nav = new Nav(led, buttonHandler, disp, seedGenerator);
    Bluetooth::begin(nav);
    Menu::begin(nav, disp, seedGenerator);
    buttonHandler.setDebounceTime(10);
}

void loop() {
    Menu::run();
    buttonHandler.poll();
}
