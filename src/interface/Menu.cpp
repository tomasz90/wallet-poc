#include "Menu.h"
#include "StateMachine.h"
#include "Disp.h"
#include "customStateMachine/CustomMachine.h"
#include "util/Pin.h"
#include "ButtonsHandler.h"
#include "util/Nav.h"
#include "util/SeedGenerator.h"

CustomMachine machine = CustomMachine();
bool Menu::firstTime = true;

void Menu::begin() {

    // STATES
//    CustomState *S0 =   machine.addState(&s0);
//    CustomState *S1_0 = machine.addState(&s1_0);
//    CustomState *S1_1 = machine.addState(&s1_1);
//    CustomState *S2 =   machine.addState(&s2);
//    CustomState *S3 =   machine.addState(&s3);
//    CustomState *S4_0 = machine.addState(&s4_0);
//    CustomState *S4_1 = machine.addState(&s4_1);
//    CustomState *S5 =   machine.addState(&s5);
//    CustomState *S6_0 = machine.addState(&s6_0);
//    CustomState *S6_1 = machine.addState(&s6_1);
//    CustomState *S6_2 = machine.addState(&s6_2);
//    CustomState *S7 = machine.addState(&s7);
    CustomState *S8_0 = machine.addState(&s8_0);
    CustomState *S8_1 = machine.addState(&s8_1);
    CustomState *S8_2 = machine.addState(&s8_2);

    // NEXT
//    S0->addTransition(S1_0,  Nav::bothCalled);
//    S1_0->addTransition(S1_1,Nav::nextCalled);
//    S1_1->addTransition(S2,  Nav::bothCalled);
//    S2->addTransition(S3,    Nav::confirmPinCalled);
//    S3->addTransition(S4_0,  Nav::confirmPinCalled);
//    S3->addTransition(S4_1,  Nav::pinMismatchCalled);
//    S4_0->addTransition(S5,  Nav::bothCalled);
//    S4_1->addTransition(S2,  Nav::bothCalled);
//
//    // PREVIOUS
//    S1_1->addTransition(S1_0,Nav::previousCalled);
//    S2->addTransition(S1_0,  Nav::dropPinCalled);
//    S3->addTransition(S2,    Nav::dropPinCalled);
//
//    S5->addTransition(S6_0,    Nav::bothCalled);
//    S6_0->addTransition(S6_1,  Nav::nextSeedScreenCalled);
//    S6_1->addTransition(S6_2,  Nav::previousCalled);
//    S6_2->addTransition(S6_1,  Nav::nextCalled);
//    S6_1->addTransition(S6_1,  Nav::nextSeedScreenCalled);
//    S6_1->addTransition(S7,    Nav::confirmSeedScreenCalled);
//    S6_2->addTransition(S6_2,  Nav::previousSeedScreenCalled);
//    S6_2->addTransition(S6_0,  Nav::firstSeedScreenCalled);
//    S7->addTransition(S8_0, Nav::bothCalled);
    S8_0->addTransition(S8_1, Nav::nextSeedScreenCalled);
    S8_1->addTransition(S8_2, Nav::previousCalled);
    S8_2->addTransition(S8_1, Nav::nextCalled);
    S8_1->addTransition(S8_1, Nav::nextSeedScreenCalled);
    S8_2->addTransition(S8_2, Nav::previousSeedScreenCalled);
    S8_2->addTransition(S8_0, Nav::firstSeedScreenCalled);
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
    doOnce([]() { Disp::drawOnlyRightBox("NEXT"); });
    Disp::blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    doOnce([]() { Disp::drawTwoBoxes("NO", "YES", false); });
    Disp::blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s1_1() {
    doOnce([]() { Disp::drawTwoBoxes("NO", "YES", true); });
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
    doOnce([]() { Disp::drawOnlyRightBox("NEXT"); });
    Disp::blinkTextWithSign("Pin confirmed!");
}

void Menu::s4_1() {
    doOnce([]() { Disp::drawOnlyLeftBox("BACK"); });
    Disp::blinkTextWithSign("Pin not matching ;(  try again...");
}

void Menu::s5() {
    doOnce([]() { Disp::drawOnlyRightBox("NEXT"); });
    Disp::blinkTextWithSign("Now please save your seed phrase!");
}

void Menu::s6_0() {
    doOnce([]() {
        Disp::clearMenu();
        Disp::drawOnlyRightBox("NEXT");
        Disp::clearText(40);
        Disp::setTextAtCenter(SeedGenerator::getCurrentWord(), 24);
    });
    Disp::blinkTextWithSign(std::to_string(SeedGenerator::currentIndex + 1) + ". word is: ", 20);
    Nav::navigateSeed(true);
}

void Menu::s6_1() {
    doOnce([]() {
        Disp::drawTwoBoxes("BACK", "NEXT", true);
        Disp::clearText(40);
        Disp::setTextAtCenter(SeedGenerator::getCurrentWord(), 24);
    });
    Disp::blinkTextWithSign(std::to_string(SeedGenerator::currentIndex + 1) + ". word is: ", 20);
    Nav::navigateSeed(true);
}

void Menu::s6_2() {
    doOnce([]() {
        Disp::drawTwoBoxes("BACK", "NEXT", false);
        Disp::clearText(40);
        Disp::setTextAtCenter(SeedGenerator::getCurrentWord(), 24);
    });
    Disp::blinkTextWithSign(std::to_string(SeedGenerator::currentIndex + 1) + ". word is: ", 20);
    Nav::navigateSeed(false);
}

void Menu::s7() {
    doOnce([]() { Disp::drawOnlyRightBox("NEXT"); });
    Disp::blinkTextWithSign("Now please confirm your seed.");
}

void Menu::s8_0() {
    doOnce([]() { Disp::drawOnlyRightBox("NEXT"); });
    Disp::blinkTextWithSign("Enter " + std::to_string(SeedGenerator::getCurrentRandom()) + " word:", 20);
    Nav::navigateSeed(true);
    readStringFromSerial();
}

void Menu::s8_1() {
    doOnce([]() { Disp::drawTwoBoxes("BACK", "NEXT", true); });
    Disp::blinkTextWithSign("Enter " + std::to_string(SeedGenerator::getCurrentRandom()) + " word:", 20);
    Nav::navigateSeed(true);
    readStringFromSerial();
}

void Menu::s8_2() {
    doOnce([]() { Disp::drawTwoBoxes("BACK", "NEXT", false); });
    Disp::blinkTextWithSign("Enter " + std::to_string(SeedGenerator::getCurrentRandom()) + " word:", 20);
    Nav::navigateSeed(false);
    readStringFromSerial();
}

void Menu::readStringFromSerial() {
    std::string incomingString;
    while (Serial.available() > 0) {
        char incomingByte = Serial.read();
        if (incomingByte == '\n') { break; }
        incomingString += incomingByte;
    }
    if (incomingString.length() > 0) {
        bool isValid = true;//SeedGenerator::validateWord(incomingString);
        if(isValid) {
            incomingString = "Invalid word!";
            Disp::clearTextCenter();
            Disp::setTextAtCenter(incomingString, 24);
            Disp::disp();
            delay(300);
            Disp::clearTextCenter();
            Disp::disp();
            delay(300);
            Disp::setTextAtCenter(incomingString, 24);
            Disp::disp();
            delay(300);
            Disp::clearTextCenter();
            Disp::disp();
            delay(300);
            Disp::setTextAtCenter(incomingString, 24);
            Disp::disp();
            delay(300);
            Disp::clearTextCenter();
            Disp::disp();
        } else {
            Disp::clearTextCenter();
            Disp::setTextAtCenter(incomingString, 24);
            Disp::disp();
        }
    }
}

