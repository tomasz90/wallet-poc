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
    CustomState *S4_0 = machine.addState(&s4_0);
    CustomState *S4_1 = machine.addState(&s4_1);
    CustomState *S5 =   machine.addState(&s5);
    CustomState *S6 = machine.addState(&s6);

    // NEXT
    S0->addTransition(S1_0,  Nav::bothCalled);
    S1_0->addTransition(S1_1,Nav::nextCalled);
    S1_1->addTransition(S2,  Nav::bothCalled);
    S2->addTransition(S3,    Nav::confirmPinCalled);
    S3->addTransition(S4_0,  Nav::confirmPinCalled);
    S3->addTransition(S4_1,  Nav::pinMismatchCalled);
    S4_0->addTransition(S5,  Nav::bothCalled);
    S4_1->addTransition(S2,  Nav::bothCalled);

    // PREVIOUS
    S1_1->addTransition(S1_0,Nav::previousCalled);
    S2->addTransition(S1_0,  Nav::dropPinCalled);
    S3->addTransition(S2,    Nav::dropPinCalled);

    //todo: to implement later
    S5->addTransition(S6,    Nav::bothCalled);

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
    doOnce([]() { Disp::drawOneBox("PROCEED?", 80); });
    Disp::blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    doOnce([]() { Disp::drawTwoBoxes("NO", "YES", true); });
    Disp::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s1_1() {
    doOnce([]() { Disp::drawTwoBoxes("NO", "YES", false); });
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

void Menu::s4_0() {
    doOnce([]() { Disp::drawOneBox("OK", 80); });
    Disp::blinkTextWithSign("Pin confirmed!");
}

void Menu::s4_1() {
    doOnce([]() { Disp::drawOneBox("GO BACK", 80); });
    Disp::blinkTextWithSign("Pin not matching ;(, try again...");
}

void Menu::s5() {
    doOnce([]() { Disp::drawOneBox("PROCEED?", 80); });
    Disp::blinkTextWithSign("Now please save your seed phrase!");
}

void Menu::s6() {
    doOnce([]() { Disp::drawOneBox("PROCEED?", 80); });
    Disp::blinkTextWithSign("Now please save your seed phrase!");
}

//void Menu::s7() {
//    doOnce([]() { Disp::drawTwoBoxes("BACK", "NEXT", false); });
//    Disp::blinkTextWithSign("Word: 1");
//}

