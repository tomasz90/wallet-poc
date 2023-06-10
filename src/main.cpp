#include <Arduino.h>
#include "seed/SeedGenerator.h"
#include "seed/SeedViewer.h"
#include "seed/SeedVerifier.h"
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
    Serial.println('\n');
    auto disp = new Disp();
    auto dataHolder = new DataHolder();
    SeedGenerator::generate(dataHolder);
    auto seedViewer = new SeedViewer(dataHolder);
    auto seedVerifier = new SeedVerifier(dataHolder);
    auto pin = new Pin();
    auto nav = new Nav(led, buttonHandler, disp, seedViewer, seedVerifier, dataHolder, pin);
    auto bt = new Bluetooth(nav, dataHolder);
    nav->setBt(bt);
    menu = new Menu(nav, disp, seedViewer, seedVerifier, pin, dataHolder);
}

void loop() {
    menu->run();
    buttonHandler.poll();
}
