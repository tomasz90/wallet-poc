#include "menu.h"
#include "StateMachine.h"
#include "display.h"
#include "interuptive.h"
#include "custom_state_machine/CustomMachine.h"

CustomMachine machine = CustomMachine();

void Menu::run() {
    machine.run();
}

void Menu::begin() {
    // STATES
    CustomState *S0 = machine.addState(&s0);
    CustomState *S1 = machine.addState(&s1);
    CustomState *S2_0 = machine.addState(&s2_0);
    CustomState *S2_1 = machine.addState(&s2_1);
    CustomState *S3 = machine.addState(&s3);

    // TRANSITIONS
    S0->addTransition(&next, &doOnTransition, S1);
    S1->addTransition(&next, &doOnTransition,S2_0);
    S2_0->addTransition(&nextSubChoice, &doOnTransition,S2_1);
    S2_1->addTransition(&nextSubChoice, &doOnTransition,S2_0);

    S3->addTransition(&previous, &doOnTransition,S2_1);
    S2_1->addTransition(&previousSubChoice, &doOnTransition,S2_0);
    S2_0->addTransition(&previousSubChoice, &doOnTransition,S2_1);
    S1->addTransition(&previous, &doOnTransition,S0);

    S2_0->addTransition(&both, &doOnTransition,S1);
    S2_1->addTransition(&both, &doOnTransition,S3);
}

void Menu::doOnTransition() {
    Serial.println("DO_ON_TRANSACTION");
}

bool Menu::next() {
    bool transition = Interaptive::isNextClicked();
    if (transition) {
        Display::clearDisplay();
        Display::setChoiceMenuNeedUpdate();
    }
    return transition;
}

bool Menu::previous() {
    bool transition = Interaptive::isPreviousClicked();
    if (transition) {
        Display::clearDisplay();
        Display::setChoiceMenuNeedUpdate();
    }
    return transition;
}

bool Menu::nextSubChoice() {
    bool transition = Interaptive::isNextClicked();
    if (transition) {
        Display::setChoiceMenuNeedUpdate();
    }
    return transition;
}

bool Menu::previousSubChoice() {
    bool transition = Interaptive::isPreviousClicked();
    if (transition) {
        Display::setChoiceMenuNeedUpdate();
    }
    return transition;
}

bool Menu::both() {
    bool transition = Interaptive::isBothClicked();
    if (transition) {
        Display::clearDisplay();
    }
    return transition;
}

void Menu::s0() {
    Display::blinkTextWithSign("Hello!");
}

void Menu::s1() {
    Display::blinkTextWithSign("Set pin:");
}

void Menu::s2_0() {
    Display::drawNo();
    Display::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s2_1() {
    Display::drawYes();
    Display::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s3() {
    Display::blinkTextWithSign("Great!");
}

