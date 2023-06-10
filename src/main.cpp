#include <Arduino.h>
#include "util/SeedVerifier.h"
#include "interface/Disp.h"
#include "interface/Menu.h"
#include "interface/Nav.h"
#include "io/Bluetooth.h"

#define PREVIOUS_BUTTON 2
#define NEXT_BUTTON 25
#define LED 23

Led* led = new Led(LED, 0, 20, 4);

Button previous(PREVIOUS_BUTTON, IN_PULLDOWN);
Button next(NEXT_BUTTON, IN_PULLDOWN);

ButtonsHandler buttonHandler(previous, next);
Menu *menu;
void setup() {
    Serial.begin(115200);
    auto disp = new Disp();
    auto seedGenerator = new SeedVerifier();
    auto pin = new Pin();
    auto nav = new Nav(led, buttonHandler, disp, seedGenerator, pin);
    auto bt = new Bluetooth(nav);
    nav->setBt(bt);
    menu = new Menu(nav, disp, seedGenerator, pin, bt);
}

void loop() {
    menu->run();
    buttonHandler.poll();
}
