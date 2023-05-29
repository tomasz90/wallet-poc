#include "Menu.h"
#include "StateMachine.h"
#include "Disp.h"
#include "custom_state_machine/CustomMachine.h"
#include "Pin.h"
#include "Led.h"
#include "ButtonsHandler.h"

bool Menu::previousCalled = false;
bool Menu::nextCalled = false;
bool Menu::bothCalled = false;
Led *Menu::led = nullptr;

CustomMachine machine = CustomMachine();

void Menu::onPrevious() {
    led->flash();
    Menu::previousCalled = true;
}
void Menu::onNext() {
    led->flash();
    Menu::nextCalled = true;
}
void Menu::onBoth() {
    led->flash();
    Menu::bothCalled = true;
}

void Menu::begin(Led *_led, ButtonsHandler &buttonHandler) {
    led = _led;

    buttonHandler.setCallbacks(onPrevious, onNext, onBoth);

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
    S0->addTransition(S1_0, &isNextCalled, &Disp::drawPin);

    S1_0->addTransition(S1_1, &isNextForPin, &Disp::drawPin);
    S1_1->addTransition(S1_2, &isNextForPin, &Disp::drawPin);
    S1_2->addTransition(S1_3, &isNextForPin, &Disp::drawPin);
    S1_3->addTransition(S2_0, &isNextForPin, &Disp::drawNo);

    S2_0->addTransition(S2_1, &isNextCalled, &Disp::drawYes);
    S2_1->addTransition(S2_0, &isPreviousCalled, &Disp::drawNo);

    S1_3->addTransition(S1_2, &isPreviousForPin, &Disp::drawPin);
    S1_2->addTransition(S1_1, &isPreviousForPin, &Disp::drawPin);
    S1_1->addTransition(S1_0, &isPreviousForPin, &Disp::drawPin);

    S2_0->addTransition(S1_0, &isBothCalled, Disp::clearText, &Disp::drawPin);
    S2_1->addTransition(S3, &isBothCalled);

    S3->addTransition(S2_1, &isBothCalled);
}

void Menu::run() {
    machine.run();
}

bool Menu::isNextCalled() {
    bool called = nextCalled;
    nextCalled = false;
    return called;
}

bool Menu::isPreviousCalled() {
    bool called = previousCalled;
    previousCalled = false;
    return called;
}

bool Menu::isBothCalled() {
    bool called = bothCalled;
    bothCalled = false;
    return called;
}

bool Menu::isNextForPin() {
    if (bothCalled && !Pin::isArrow()) {
        Pin::setPinNumber();
        bothCalled = false;
        return true;
    }
    return false;
}

bool Menu::isPreviousForPin() {
    if (bothCalled && Pin::isArrow()) {
        Pin::unsetPinNumber();
        bothCalled = false;
        return true;
    }
    return false;
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
    if (isNextCalled()) {
        Pin::incrementCurrentNumber(position);
        Disp::drawPin();
    }
    if (isPreviousCalled()) {
        Pin::decrementCurrentNumber(position);
        Disp::drawPin();
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

