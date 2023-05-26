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
    State* S0 = machine.addState(&s0);
    State* S1 = machine.addState(&s1);
    State* S2_0 = machine.addState(&s2_0);
    State* S2_1 = machine.addState(&s2_1);
    State* S3 = machine.addState(&s3);
    State* S4 = machine.addState(&s4);
    State* S5 = machine.addState(&s5);

    S0->addTransition(&next,S1);
    S1->addTransition(&next, S2_0);
    S2_0->addTransition(&next, S2_1);
    S2_1->addTransition(&next, S2_0);
    S3->addTransition(&next,S4);

    S4->addTransition(&previous,S3);
    S3->addTransition(&previous, S2_1);
    S2_1->addTransition(&previous, S2_0);
    S2_0->addTransition(&previous, S2_1);
    S1->addTransition(&previous,S0);
    S0->addTransition(&previous,S4);

    S2_0->addTransition(&both, S1);
    S2_1->addTransition(&both, S3);

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

void Menu::s0() {
    Display::blinkTextWithSign("Hello!");
}

void Menu::s1() {
    Display::blinkTextWithSign("Set pin:");
}

void Menu::s2_0() {
    Display::blinkTextWithSign("Do you want to set as new device?");
    DisplayChoice::drawNo();
}

void Menu::s2_1() {
    Display::blinkTextWithSign("Do you want to set as new device?");
    DisplayChoice::drawYes();
}

void Menu::s3() {
    Display::blinkTextWithSign("s3");
}

void Menu::s4() {
    Display::blinkTextWithSign("Enter your seed?");
}

void Menu::s5() {
    Display::blinkTextWithSign("confirmed");
}

