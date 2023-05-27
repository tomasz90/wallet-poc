#include "menu.h"
#include "StateMachine.h"
#include "display.h"
#include "button/listener.h"
#include "custom_state_machine/CustomMachine.h"
#include "pin.h"

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
    S1_3->addTransition(S2_0, &noHandle, &Disp::drawNo);

    S2_0->addTransition(S2_1, &next,  &Disp::drawYes);
    S2_1->addTransition(S2_0, &previous, &Disp::drawNo);

    S1_3->addTransition(S1_2, &noHandle, &Disp::drawPin);
    S1_2->addTransition(S1_1, &noHandle, &Disp::drawPin);
    S1_1->addTransition(S1_0, &noHandle, &Disp::drawPin);

    S2_0->addTransition(S1_0, &both);
    S2_1->addTransition(S3, &both);

    S3->addTransition(S2_1, &both);

}

bool Menu::next() {
    return Listener::isNextClicked();
}

bool Menu::previous() { return Listener::isPreviousClicked(); }

bool Menu::both() { return Listener::isBothClicked(); }

bool Menu::noHandle() { return false; }

void Menu::anyTransition() {
    Disp::firstTime = true;
}
void Menu::s0() {
    Disp::blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    Disp::blinkTextWithSign("Set pin:");
    enterPin(0);
}

void Menu::s1_1() {
    Disp::blinkTextWithSign("Set pin:");
    enterPin(1);

}

void Menu::s1_2() {
    Disp::blinkTextWithSign("Set pin:");
    enterPin(2);

}

void Menu::s1_3() {
    Disp::blinkTextWithSign("Set pin:");
    enterPin(3);
}

void Menu::enterPin(int position) {
    if(next()) {
        Pin::incrementCurrentNumber(position);
        Disp::drawPin();
    }
    if(previous()) {
        Pin::decrementCurrentNumber(position);
        Disp::drawPin();
    }
    if(both()) {
        if(Pin::getCurrentNumber() == -1) {
            Pin::unsetPinAt(position);
            Disp::drawPin();
            machine.transitionTo(machine.currentState - 1);
            return;
        }
        Pin::setPinAt(position);
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

