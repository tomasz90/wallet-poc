#include "Menu.h"
#include "StateMachine.h"
#include "Disp.h"
#include "custom_state_machine/CustomMachine.h"
#include "Pin.h"
#include "ButtonsHandler.h"
#include "Nav.h"

CustomMachine machine = CustomMachine();

void Menu::begin() {

    // STATES
    CustomState *S0 = machine.addState(&s0);
    CustomState *S1_0 = machine.addState(&s1_0);
    CustomState *S1_1 = machine.addState(&s1_1);
    CustomState *S1_2 = machine.addState(&s1_2);
    CustomState *S1_3 = machine.addState(&s1_3);

    CustomState *S2_0 = machine.addState(&s2_0);
    CustomState *S2_1 = machine.addState(&s2_1);
    CustomState *S3 = machine.addState(&s3);

    // TRANSITIONS
    S0->addTransition(S1_0, &Nav::isNext, &Disp::drawPin);

    S1_0->addTransition(S1_1, &Nav::isNextPin, &Disp::drawPin);
    S1_1->addTransition(S1_2, &Nav::isNextPin, &Disp::drawPin);
    S1_2->addTransition(S1_3, &Nav::isNextPin, &Disp::drawPin);
    S1_3->addTransition(S2_0, &Nav::isNextPin, &Disp::drawNo);

    S2_0->addTransition(S2_1, &Nav::isNext, &Disp::drawYes);
    S2_1->addTransition(S2_0, &Nav::isPrevious, &Disp::drawNo);

    S1_3->addTransition(S1_2, &Nav::isPreviousPin, &Disp::drawPin);
    S1_2->addTransition(S1_1, &Nav::isPreviousPin, &Disp::drawPin);
    S1_1->addTransition(S1_0, &Nav::isPreviousPin, &Disp::drawPin);

    S2_0->addTransition(S1_0, &Nav::isBoth, Disp::clearText, &Disp::drawPin);
    S2_1->addTransition(S3, &Nav::isBoth, Disp::clearMenu);

    S3->addTransition(S2_0, &Nav::isBoth, &Disp::drawNo);
}

void Menu::run() {
    machine.run();
}

void Menu::s0() {
    Disp::blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(0);
}

void Menu::s1_1() {
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(1);
}

void Menu::s1_2() {
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(2);
}

void Menu::s1_3() {
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(3);
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
