#include <Arduino.h>
#include <EEPROM.h>
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
    EEPROM.begin(115);

    auto disp = new Disp();
    auto dataHolder = new DataHolder();
    auto seedViewer = new SeedViewer();
    auto seedVerifier = new SeedVerifier();
    auto pin = new Pin();
    auto nav = new Nav(led, buttonHandler, disp, seedViewer, seedVerifier, dataHolder, pin);
    auto bt = new Bluetooth(nav, dataHolder);

    // THIS HAS TO BA AFTER BT INIT TO GENERATE TRUE RANDOM NUMBERS
    SeedGenerator::generate(seedViewer, seedVerifier);
    nav->setBt(bt);
    menu = new Menu(nav, disp, seedViewer, seedVerifier, dataHolder, pin);

    dataHolder->printInfo();
}

void loop() {
    menu->run();
    buttonHandler.poll();
}
