#include <Wire.h>
#include <Arduino.h>
#include "util/seed.h"
#include "util/display.h"
#include "util/interuptive.h"
#include "../lib/StateMachine/src/StateMachine.h"

#define NEXT_BUTTON 0
#define PREVIOUS_BUTTON 34

bool next(){
    return Interaptive::nextClicked();
}

void welcome() {
    Display::setText("Hello!");
}

void newOrOld() {
    Display::setText("NewOrdOld");
}

void generateSeed() {
    Display::setText("generateSeed");
}

StateMachine machine = StateMachine();

State* S0 = machine.addState(&welcome);
State* S1 = machine.addState(&newOrOld);
State* S2 = machine.addState(&generateSeed);

void setup() {
    Serial.begin(115200);
    pinMode(NEXT_BUTTON, INPUT);
    pinMode(PREVIOUS_BUTTON, INPUT);
    Seed::createMnemonic();
    Display::begin();
    Interaptive::begin(PREVIOUS_BUTTON, NEXT_BUTTON);

    S0->addTransition(&next,S1);  // S0 transition to S1
    S1->addTransition(&next,S2);  // S1 transition to S2
    S2->addTransition(&next,S0);  // S1 transition to S2
}

void loop() {
    machine.run();
}
