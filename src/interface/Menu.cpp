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
    CustomState *S0 =   machine.addState(&s0);

    CustomState *S1_0 = machine.addState(&s1_0);
    CustomState *S1_1 = machine.addState(&s1_1);

    CustomState *S2_0 = machine.addState(&s2_0);
    CustomState *S2_1 = machine.addState(&s2_1);
    CustomState *S2_2 = machine.addState(&s2_2);
    CustomState *S2_3 = machine.addState(&s2_3);

    CustomState *S3_0 = machine.addState(&s3_0);
    CustomState *S3_1 = machine.addState(&s3_1);
    CustomState *S3_2 = machine.addState(&s3_2);
    CustomState *S3_3 = machine.addState(&s3_3);

    CustomState *S4 =   machine.addState(&s4);

    // NEXT
    S0->addTransition(S1_0,   &Nav::isBoth);

    S1_0->addTransition(S1_1, &Nav::isNext);
    S1_1->addTransition(S2_0, &Nav::isBoth);

    S2_0->addTransition(S2_1, &Nav::isNextPin);
    S2_1->addTransition(S2_2, &Nav::isNextPin);
    S2_2->addTransition(S2_3, &Nav::isNextPin);
    S2_3->addTransition(S3_0, &Nav::isNextPin);

    S3_0->addTransition(S3_1, &Nav::isNextPin);
    S3_1->addTransition(S3_2, &Nav::isNextPin);
    S3_2->addTransition(S3_3, &Nav::isNextPin);
    S3_3->addTransition(S4,   &Nav::isNextPin);

    // PREVIOUS
    S1_1->addTransition(S1_0, &Nav::isPrevious);

    S2_0->addTransition(S1_0, &Nav::isPreviousPin);
    S2_1->addTransition(S2_0, &Nav::isPreviousPin);
    S2_2->addTransition(S2_1, &Nav::isPreviousPin);
    S2_3->addTransition(S2_2, &Nav::isPreviousPin);

    S3_0->addTransition(S2_0, &Nav::isPreviousPin);
    S3_1->addTransition(S3_0, &Nav::isPreviousPin);
    S3_2->addTransition(S3_1, &Nav::isPreviousPin);
    S3_3->addTransition(S3_2, &Nav::isPreviousPin);

    //todo: to implement later
    S4->addTransition(S0, &Nav::isBoth);

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
    doOnce([]() { Disp::drawOneBox("Proceed?", 80); });
    Disp::blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    doOnce(&Disp::drawNo);
    Disp::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s1_1() {
    doOnce(&Disp::drawYes);
    Disp::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s2_0() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(0);
}

void Menu::s2_1() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(1);
}

void Menu::s2_2() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(2);
}

void Menu::s2_3() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin(3);
}

void Menu::s3_0() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Confirm pin:");
    Nav::enterPin(0);
}

void Menu::s3_1() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Confirm pin:");
    Nav::enterPin(1);
}

void Menu::s3_2() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Confirm pin:");
    Nav::enterPin(2);
}

void Menu::s3_3() {
    doOnce(&Disp::drawPin);
    Disp::blinkTextWithSign("Confirm pin:");
    Nav::enterPin(3);
}

void Menu::s4() {
    doOnce([]() { Disp::drawOneBox("OK", 80); });
    Disp::blinkTextWithSign("Pin confirmed!");
}

