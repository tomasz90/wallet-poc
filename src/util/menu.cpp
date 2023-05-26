#include "menu.h"
#include "StateMachine.h"
#include "display.h"
#include "interuptive.h"
#include "display_choice.h"

StateMachine machine = StateMachine();

void Menu::run() {
    machine.run();
}

void Menu::begin() {
    State* S0 = machine.addState(&welcome);
    State* S1 = machine.addState(&setPin);
    State* S2 = machine.addState(&newOrOld);
    State* S3 = machine.addState(&generateSeed);
    State* S4 = machine.addState(&enterSeed);
    State* S5 = machine.addState(&confirm);

    S0->addTransition(&next,S1);
    S1->addTransition(&next,S2);
    S2->addTransition(&next,S3);
    S3->addTransition(&next,S4);

    S4->addTransition(&previous,S3);
    S3->addTransition(&previous,S2);
    S2->addTransition(&previous,S1);
    S1->addTransition(&previous,S0);
    S0->addTransition(&previous,S4);

    S0->addTransition(&both,S5);
    S1->addTransition(&both,S5);
    S2->addTransition(&both,S5);
    S3->addTransition(&both,S5);
    S4->addTransition(&both,S5);

    S5->addTransition(&both,S0);
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
    DisplayChoice::drawNo();
    Display::setText("Hello!");
    delay(500);
    Display::clearText();
    delay(500);
}

void Menu::setPin() {
    Display::animateText("Set pin:");
}

void Menu::newOrOld() {
    Display::animateText("Do you want to set as new device?");
}

void Menu::generateSeed() {
    Display::animateText("generateSeed");
}

void Menu::enterSeed() {
    Display::animateText("Enter your seed?");
}

void Menu::confirm() {
    Display::animateText("confirmed");
}

