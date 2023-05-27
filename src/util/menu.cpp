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
    S1->addTransition(&next, &displayNoMenu,S2_0);
    S2_0->addTransition(&next, &displayYesMenu, S2_1);
    S2_1->addTransition(&next, &displayNoMenu, S2_0);

    S3->addTransition(&previous, &doOnTransition,S2_1);
    S2_1->addTransition(&previous, &doOnTransition,S2_0);
    S2_0->addTransition(&previous, &doOnTransition,S2_1);
    S1->addTransition(&previous, &doOnTransition,S0);

    S2_0->addTransition(&both, &doOnTransition,S1);
    S2_1->addTransition(&both, &doOnTransition,S3);
}

void Menu::displayNoMenu() {
    Display::clearDisplay();
    Display::drawNo();
}

void Menu::displayYesMenu() {
    Display::clearDisplay();
    Display::drawYes();
}

void Menu::doOnTransition() {
    Display::clearDisplay();
    Serial.println("DO_ON_TRANSACTION");
}

bool Menu::next() {
    return Interaptive::isNextClicked();
}

bool Menu::previous() {
    return Interaptive::isPreviousClicked();
}

bool Menu::both() {
    return Interaptive::isBothClicked();
}

void Menu::s0() {
    Display::blinkTextWithSign("Hello!");
}

void Menu::s1() {
    Display::blinkTextWithSign("Set pin:");
}

void Menu::s2_0() {
    Display::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s2_1() {
    Display::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s3() {
    Display::blinkTextWithSign("Great!");
}

