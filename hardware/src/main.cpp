#include <Arduino.h>
#include <EEPROM.h>
#include "seed/SeedGenerator.h"
#include "seed/SeedViewer.h"
#include "seed/SeedVerifier.h"
#include "interface/Disp.h"
#include "interface/menu/Menu.h"
#include "interface/Nav.h"
#include "io/Bluetooth.h"
#include "util/Battery.h"

#define PREVIOUS_BUTTON 2
#define NEXT_BUTTON 15
#define LED 23
#define BATTERY_PIN 33
#define SDA 19
#define SCL 23

Led* led = new Led(LED, 0, 20, 4);

Button previous(PREVIOUS_BUTTON, IN_PULLUP);
Button next(NEXT_BUTTON, IN_PULLUP);
ButtonsHandler buttonHandler(previous, next);

Menu* menu;
void setup() {
    Serial.begin(115200);
    Serial.println('\n');
    EEPROM.begin(115);
    Wire.begin(SDA, SCL);
    auto battery = new Battery(BATTERY_PIN);
    auto disp = new Disp();
    auto repository = new Repository();
    auto seedViewer = new SeedViewer();
    auto seedVerifier = new SeedVerifier();
    SeedGenerator::generate(seedViewer, seedVerifier);
    esp_sleep_enable_ext0_wakeup(static_cast<gpio_num_t>(NEXT_BUTTON), 0);

    auto pin = new Pin();
    menu = new Menu(disp, seedViewer, seedVerifier, repository, pin, led, buttonHandler, battery);

    repository->printInfo();
}

void loop() {
    menu->run();
    buttonHandler.poll();
}
