#include <Wire.h>
#include <Arduino.h>
#include "util/seed.h"
#include "util/display.h"
#include "util/interuptive.h"

#define NEXT_BUTTON 35
#define PREVIOUS_BUTTON 34

void setup() {
    Serial.begin(115200);
    pinMode(NEXT_BUTTON, INPUT);
    pinMode(PREVIOUS_BUTTON, INPUT);
    Seed::createMnemonic();
    Display::begin();
    Interaptive::begin(PREVIOUS_BUTTON, NEXT_BUTTON);
}

void loop() {
    if (Interaptive::wordIndex > 11) {
        Display::setText("Done!");
    } else if (Interaptive::wordIndex != -1) {
        Display::animateText();
    }
}
