#include "menu.h"
#include "StateMachine.h"
#include "display.h"
#include "interuptive.h"

StateMachine machine = StateMachine();

Menu::Menu() = default;

void Menu::run() {
    machine.run();
}

void Menu::begin() {
    State* S0 = machine.addState(&welcome);
    State* S1 = machine.addState(&newOrOld);
    State* S2 = machine.addState(&generateSeed);

    S0->addTransition(&next,S1);  // S0 transition to S1
    S1->addTransition(&next,S2);  // S1 transition to S2
    S2->addTransition(&next,S0);  // S2 transition to S0
}

bool Menu::next(){
    return Interaptive::nextClicked();
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

