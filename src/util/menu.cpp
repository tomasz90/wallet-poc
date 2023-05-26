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
    State* S2 = machine.addState(&s2);
    State* S3 = machine.addState(&s3);
    State* S4 = machine.addState(&s4);
    State* S5 = machine.addState(&s5);

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

void Menu::s0() {
    Display::animateText("Hello!", "Hello! >");
    DisplayChoice::drawNo();
}

void Menu::s1() {
    //Display::animateText("Set pin:");
}

void Menu::s2() {
    //Display::animateText("Do you want to set as new device?");
}

void Menu::s3() {
    //Display::animateText("s3");
}

void Menu::s4() {
    //Display::animateText("Enter your seed?");
}

void Menu::s5() {
    //Display::animateText("confirmed");
}

