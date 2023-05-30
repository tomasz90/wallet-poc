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
    CustomState *S2 =   machine.addState(&s2);
    CustomState *S3 =   machine.addState(&s3);
    CustomState *S4 =   machine.addState(&s4);
    CustomState *S5 =   machine.addState(&s5);

    // NEXT
    S0->addTransition(S1_0,   Nav::bothCalled);
    S1_0->addTransition(S1_1, Nav::nextCalled);
    S1_1->addTransition(S2,   Nav::bothCalled);
    S2->addTransition(S3,     Nav::nextPinBothCalled);
    S3->addTransition(S4,     Nav::nextPinBothCalled);
    S4->addTransition(S5,     Nav::bothCalled);

    // PREVIOUS
    S1_1->addTransition(S1_0, Nav::previousCalled);
    S2->addTransition(S1_0,   Nav::previousPinBothCalled);
    S3->addTransition(S2,     Nav::previousPinBothCalled);

    //todo: to implement later
    S5->addTransition(S0,     Nav::bothCalled);

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

void Menu::s2() {
    doOnce([]() {
        Pin::setMode(PinMode::SET);
        Disp::drawPin();
    });

    Disp::blinkTextWithSign("Set pin:");
    Nav::enterPin();
}

void Menu::s3() {
    doOnce([]() {
        Pin::setMode(PinMode::CONFIRM);
        Disp::drawPin();
    });
    Disp::blinkTextWithSign("Confirm pin:");
    Nav::enterPin();
}

void Menu::s4() {
    doOnce([]() { Disp::drawOneBox("OK", 80); });
    Disp::blinkTextWithSign("Pin confirmed!");
}

void Menu::s5() {
    Disp::blinkTextWithSign("Now please save your seed phrase!");
}

