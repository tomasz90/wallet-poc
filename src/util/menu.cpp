#include "menu.h"
#include "StateMachine.h"
#include "display.h"
#include "interuptive.h"

StateMachine machine = StateMachine();
uint8_t Menu::led;

Menu::Menu() = default;

void Menu::run() {
    machine.run();
}

void Menu::begin(uint8_t _led) {
    pinMode(_led, OUTPUT);
    led = _led;
    State* S0 = machine.addState(&welcome);
    State* S1 = machine.addState(&newOrOld);
    State* S2 = machine.addState(&generateSeed);

    S0->addTransition(&next,S1);  // S0 transition to S1
    S1->addTransition(&next,S2);  // S1 transition to S2
    S2->addTransition(&next,S0);  // S2 transition to S0
}

bool Menu::next(){
    bool clicked = Interaptive::nextClicked();
    flashLed(clicked);
    return clicked;
}

void Menu::flashLed(bool flash) {
    if(flash) {
        digitalWrite(led, HIGH);
        delay(200);
        digitalWrite(led, LOW);
    }
}

void Menu::welcome() {
    Display::animateText();
}

void Menu::newOrOld() {
    Display::setText("NewOrdOld");
}

void Menu::generateSeed() {
    Display::setText("generateSeed");
}

