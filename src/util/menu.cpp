#include "menu.h"
#include "StateMachine.h"
#include "display.h"
#include "button/listener.h"
#include "custom_state_machine/CustomMachine.h"

CustomMachine machine = CustomMachine();

void Menu::run() {
    machine.run();
}

void Menu::begin() {
    // STATES
    CustomState *S0 = machine.addState(&s0);
    CustomState *S1_0 = machine.addState(&s1_0);
    CustomState *S1_1 = machine.addState(&s1_1);
    CustomState *S1_2 = machine.addState(&s1_2);
    CustomState *S1_3 = machine.addState(&s1_3);
    CustomState *S1_4 = machine.addState(&s1_4);

    CustomState *S2_0 = machine.addState(&s2_0);
    CustomState *S2_1 = machine.addState(&s2_1);
    CustomState *S3 = machine.addState(&s3);

    // TRANSITIONS
    S0->addTransition(S1_0, &next, &Disp::drawPinAsterisks);

    S1_0->addTransition(S1_1, &pinNext, &Disp::drawPinAsterisks);
    S1_1->addTransition(S1_2, &pinNext, &Disp::drawPinAsterisks);
    S1_2->addTransition(S1_3, &pinNext, &Disp::drawPinAsterisks);
    S1_3->addTransition(S1_4, &pinNext, &Disp::drawPinAsterisks);
    S1_4->addTransition(S2_0, &pinNext, &Disp::drawPinAsterisks);

    S2_0->addTransition(S2_1, &next, &Disp::drawYes);
    S2_1->addTransition(S2_0, &next, &Disp::drawNo);

    S3->addTransition(S2_1, &previous, &Disp::drawNo);
    S2_1->addTransition(S2_0, &previous, &Disp::drawNo);
    S2_0->addTransition(S2_1, &previous, &Disp::drawYes);

    S1_4->addTransition(S1_3, &pinPrevious, &Disp::drawPinAsterisks);
    S1_3->addTransition(S1_2, &pinPrevious, &Disp::drawPinAsterisks);
    S1_2->addTransition(S1_1, &pinPrevious, &Disp::drawPinAsterisks);
    S1_1->addTransition(S1_0, &pinPrevious, &Disp::drawPinAsterisks);
    S1_0->addTransition(S0, &previous);

    S2_0->addTransition(S1_0, &both);
    S2_1->addTransition(S3, &both);
}

bool Menu::next() { return Listener::isNextClicked(); }

bool Menu::previous() { return Listener::isPreviousClicked(); }

bool Menu::both() { return Listener::isBothClicked(); }

bool Menu::pinNext() { return false; }

bool Menu::pinPrevious() { return false; }

void Menu::s0() {
    Disp::blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    Disp::blinkTextWithSign("Set pin:");
}

void Menu::s1_1() {
    Disp::blinkTextWithSign("Set pin:");
}

void Menu::s1_2() {
    Disp::blinkTextWithSign("Set pin:");
}

void Menu::s1_3() {
    Disp::blinkTextWithSign("Set pin:");
}

void Menu::s1_4() {
    Disp::blinkTextWithSign("Set pin:");
}

void Menu::s2_0() {
    Disp::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s2_1() {
    Disp::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s3() {
    Disp::blinkTextWithSign("Great!");
}

