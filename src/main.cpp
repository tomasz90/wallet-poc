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
Menu *menu;
void setup() {
    Serial.begin(115200);
    auto disp = new Disp();
    auto seedGenerator = new SeedGenerator();
    auto nav = new Nav(led, buttonHandler, disp, seedGenerator);
    menu = new Menu(nav, disp, seedGenerator);
    Bluetooth::begin(nav);
}

void loop() {
    menu->run();
    buttonHandler.poll();
}
