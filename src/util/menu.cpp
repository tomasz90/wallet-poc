#include "menu.h"
#include "StateMachine.h"
#include "display.h"
#include "interuptive.h"

StateMachine machine = StateMachine();

void Menu::run() {
    machine.run();
}

void Menu::begin() {
    // STATES
    State *S0 = machine.addState(&s0);
    State *S1 = machine.addState(&s1);
    State *S2_0 = machine.addState(&s2_0);
    State *S2_1 = machine.addState(&s2_1);
    State *S3 = machine.addState(&s3);

    // TRANSITIONS
    S0->addTransition(&next, S1);
    S1->addTransition(&next, S2_0);
    S2_0->addTransition(&nextSubChoice, S2_1);
    S2_1->addTransition(&nextSubChoice, S2_0);

    S3->addTransition(&previous, S2_1);
    S2_1->addTransition(&previousSubChoice, S2_0);
    S2_0->addTransition(&previousSubChoice, S2_1);
    S1->addTransition(&previous, S0);

    S2_0->addTransition(&both, S1);
    S2_1->addTransition(&both, S3);
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

