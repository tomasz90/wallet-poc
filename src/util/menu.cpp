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

    CustomState *S2_0 = machine.addState(&s2_0);
    CustomState *S2_1 = machine.addState(&s2_1);
    CustomState *S3 = machine.addState(&s3);

    // TRANSITIONS
    S0->addTransition(S1_0, &next, &Disp::drawPin);

    S1_0->addTransition(S1_1, &noHandle, &Disp::drawPin);
    S1_1->addTransition(S1_2, &noHandle, &Disp::drawPin);
    S1_2->addTransition(S1_3, &noHandle, &Disp::drawPin);
    S1_3->addTransition(S2_0, &noHandle, &Disp::drawPin);

    S2_0->addTransition(S2_1, &next, &Disp::drawYes);
    S2_1->addTransition(S2_0, &next, &Disp::drawNo);

    S3->addTransition(S2_1, &previous, &Disp::drawNo);
    S2_1->addTransition(S2_0, &previous, &Disp::drawNo);
    S2_0->addTransition(S2_1, &previous, &Disp::drawYes);

    S1_3->addTransition(S1_2, &noHandle, &Disp::drawPin);
    S1_2->addTransition(S1_1, &noHandle, &Disp::drawPin);
    S1_1->addTransition(S1_0, &noHandle, &Disp::drawPin);
    S1_0->addTransition(S0, &previous);

    S2_0->addTransition(S1_0, &both);
    S2_1->addTransition(S3, &both);
}

bool Menu::next() { return Listener::isNextClicked(); }

bool Menu::previous() { return Listener::isPreviousClicked(); }

bool Menu::both() { return Listener::isBothClicked(); }

bool Menu::noHandle() { return false; }

void Menu::s0() {
    Disp::blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    Disp::blinkTextWithSign("Set pin:");
    enterPin(0);
}

void Menu::s1_1() {
    Disp::blinkTextWithSign("Set pin:");
    enterPin(2);

}

void Menu::s1_2() {
    Disp::blinkTextWithSign("Set pin:");
    enterPin(4);

}

void Menu::s1_3() {
    Disp::blinkTextWithSign("Set pin:");
    enterPin(6);
}

void Menu::enterPin(const int& position) {
    if(next()) {
        Disp::incrementPinNumber();
        Disp::pin.replace(position, 1, Disp::getPinChar());
        Disp::drawPin();
    }
    if(previous()) {
        Disp::decrementPinNumber();
        Disp::pin.replace(position, 1, Disp::getPinChar());
        Disp::drawPin();
    }
    if(both()) {
        if(Disp::pinNumber == -1) {
            machine.transitionTo(machine.currentState - 1);
            Disp::pin.replace(position, 1, "*");
            Disp::drawPin();
            return;
        }
        Disp::randomPinNumber();
        Disp::pin.replace(position, 1, "$");
        Disp::drawPin();
        machine.transitionTo(machine.currentState + 1);
    }
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

