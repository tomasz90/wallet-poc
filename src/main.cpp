#include <Arduino.h>
#include <EEPROM.h>
#include "seed/SeedGenerator.h"
#include "seed/SeedViewer.h"
#include "seed/SeedVerifier.h"
#include "interface/Disp.h"
#include "interface/menu/Menu.h"
#include "interface/Nav.h"
#include "io/Bluetooth.h"

#define PREVIOUS_BUTTON 2
#define NEXT_BUTTON 25
#define LED 23

Led* led = new Led(LED, 0, 20, 4);

Button previous(PREVIOUS_BUTTON, IN_PULLDOWN);
Button next(NEXT_BUTTON, IN_PULLDOWN);
ButtonsHandler buttonHandler(previous, next);

Menu* menu;
void setup() {
    Serial.begin(115200);
    Serial.println('\n');
    EEPROM.begin(115);

    auto disp = new Disp();
    auto repository = new Repository();
    auto seedViewer = new SeedViewer();
    auto seedVerifier = new SeedVerifier();
    SeedGenerator::generate(seedViewer, seedVerifier);

    auto pin = new Pin();
    menu = new Menu(disp, seedViewer, seedVerifier, repository, pin, led, buttonHandler);

    repository->printInfo();
}

void loop() {
    menu->run();
    buttonHandler.poll();
}
