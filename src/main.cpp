#include <Wire.h>
#include <Arduino.h>
#include "util/seed.h"
#include "util/display.h"
#include "util/interuptive.h"

#define BUTTON 35

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON, INPUT);
    attachInterrupt(BUTTON, Interaptive::nextWord(), RISING);
    Seed::createMnemonic();
    Display::begin();
}

void loop() {
    if (Interaptive::wordIndex > 11) {
        Display::setText("Done!");
    } else if (Interaptive::wordIndex != -1) {
        Display::animateText();
    }
}
