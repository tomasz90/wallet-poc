#include "Menu.h"
#include "StateMachine.h"
#include "Disp.h"
#include "customStateMachine/CustomMachine.h"
#include "util/Pin.h"
#include "ButtonsHandler.h"
#include "util/Nav.h"

CustomMachine machine = CustomMachine();
bool Menu::firstTime = true;

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
    S0->addTransition(S1_0, &Nav::isBoth);

    S1_0->addTransition(S1_1, &Nav::isNextPin);
    S1_1->addTransition(S1_2, &Nav::isNextPin);
    S1_2->addTransition(S1_3, &Nav::isNextPin);
    S1_3->addTransition(S2_0, &Nav::isNextPin);

    S2_0->addTransition(S2_1, &Nav::isNext);
    S2_1->addTransition(S2_0, &Nav::isPrevious);

    S1_3->addTransition(S1_2, &Nav::isPreviousPin);
    S1_2->addTransition(S1_1, &Nav::isPreviousPin);
    S1_1->addTransition(S1_0, &Nav::isPreviousPin);

    S2_0->addTransition(S1_0, &Nav::isBoth, Disp::clearText);
    S2_1->addTransition(S3, &Nav::isBoth, Disp::clearMenu);

    S3->addTransition(S2_0, &Nav::isBoth);
}

void Menu::run() {
    machine.run();
}

void Menu::doOnce(void (*_doOnce)()) {
    if (firstTime) {
        firstTime = false;
        _doOnce();
    }
}

void Menu::s0() {
    doOnce([]() { Disp::drawOneBox("Proceed?", 80, 40); });
    Disp::blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(0);
}

void Menu::s1_1() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(1);
}

void Menu::s1_2() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(2);
}

void Menu::s1_3() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(3);
}

void Menu::s2_0() {
    doOnce(&Disp::drawNo);
    Disp::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s2_1() {
    doOnce(&Disp::drawYes);
    Disp::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s3() {
    //doOnce();
    Disp::blinkTextWithSign("Great!");
}

