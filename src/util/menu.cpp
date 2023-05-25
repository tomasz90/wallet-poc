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
    State* S3 = machine.addState(&confirm);

    S0->addTransition(&next,S1);  // S0 transition to S1
    S1->addTransition(&next,S2);  // S1 transition to S2
    S2->addTransition(&next,S0);  // S2 transition to S0

    S2->addTransition(&previous,S1);  // S0 transition to S1
    S1->addTransition(&previous,S0);  // S1 transition to S2
    S0->addTransition(&previous,S2);  // S2 transition to S0

    S0->addTransition(&both,S3);
    S1->addTransition(&both,S3);
    S2->addTransition(&both,S3);

    S3->addTransition(&both,S0);
}

bool Menu::next(){
    return Interaptive::nextClicked();
}

bool Menu::previous(){
    return Interaptive::previousClicked();
}

bool Menu::both(){
    return Interaptive::bothClicked();
}

void Menu::welcome() {
    Display::animateText("0");
}

void Menu::newOrOld() {
    Display::animateText("1");
}

void Menu::generateSeed() {
    Display::animateText("2");
}

void Menu::confirm() {
    Display::animateText("confirmed");
}

