#include "Menu.h"
#include "customStateMachine/CustomMachine.h"
#include "util/Pin.h"
#include "ButtonsHandler.h"
#include "util/Nav.h"
#include "util/SeedGenerator.h"
#include "io/Bluetooth.h"

CustomMachine machine = CustomMachine();
bool Menu::firstTime = true;

CustomState *S9_0 = nullptr;
CustomState *S9_1 = nullptr;
CustomState *S9_2 = nullptr;
CustomState *S9_3 = nullptr;
CustomState *S9_4 = nullptr;

Nav *Menu::nav;
Disp *Menu::disp;

using std::string;

void Menu::begin(Nav *_nav, Disp *_disp) {
    nav = _nav;
    disp = _disp;
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
//    CustomState *S8_0 = machine.addState(&s8_0);
//    CustomState *S8_1 = machine.addState(&s8_1);
//    CustomState *S8_2 = machine.addState(&s8_2);
    S9_0 = machine.addState(&s9_0);
    S9_1 = machine.addState(&s9_1);
    S9_2 = machine.addState(&s9_2);
    S9_3 = machine.addState(&s9_3);
    S9_4 = machine.addState(&s9_4);

    // NEXT
//    S0->addTransition(S1_0,  nav->bothCalled);
//    S1_0->addTransition(S1_1,nav->nextCalled);
//    S1_1->addTransition(S2,  nav->bothCalled);
//    S2->addTransition(S3,    nav->confirmPinCalled);
//    S3->addTransition(S4_0,  nav->confirmPinCalled);
//    S3->addTransition(S4_1,  nav->pinMismatchCalled);
//    S4_0->addTransition(S5,  nav->bothCalled);
//    S4_1->addTransition(S2,  nav->bothCalled);

    S9_0->addTransition(S9_1, nav->btConnectedCalled);
    S9_1->addTransition(S9_2, nav->receivedTxCalled);
    S9_2->addTransition(S9_3, nav->nextCalled);
    S9_3->addTransition(S9_4, nav->bothCalled);

//    // PREVIOUS
//    S1_1->addTransition(S1_0,nav->previousCalled);
//    S2->addTransition(S1_0,  nav->dropPinCalled);
//    S3->addTransition(S2,    nav->dropPinCalled);
//
//    S5->addTransition(S6_0,    nav->bothCalled);
//    S6_0->addTransition(S6_1,nav->nextSeedScreenCalled);
//    S6_1->addTransition(S6_2,nav->previousCalled);
//    S6_2->addTransition(S6_1,nav->nextCalled);
//    S6_1->addTransition(S6_1,nav->nextSeedScreenCalled);
//    S6_1->addTransition(S7,  nav->confirmSeedScreenCalled);
//    S6_2->addTransition(S6_2,nav->previousSeedScreenCalled);
//    S6_2->addTransition(S6_0,nav->firstSeedScreenCalled);
//    S7->addTransition(S8_0,  nav->bothCalled);
//    S8_0->addTransition(S8_1,nav->nextSeedScreenCalled);
//    S8_1->addTransition(S8_2,nav->previousCalled);
//    S8_2->addTransition(S8_1,nav->nextCalled);
//    S8_1->addTransition(S8_1,nav->nextSeedScreenCalled);
//    S8_2->addTransition(S8_2,nav->previousSeedScreenCalled);
//    S8_2->addTransition(S8_0,nav->firstSeedScreenCalled);

    S9_1->addTransition(S9_0, nav->btDisconnectedCalled);
    S9_2->addTransition(S9_0, nav->btDisconnectedCalled);
    S9_3->addTransition(S9_0, nav->btDisconnectedCalled);

    S9_2->addTransition(S9_1, nav->bothCalled);
    S9_3->addTransition(S9_2, nav->previousCalled);
    S9_4->addTransition(S9_1, nav->bothCalled);

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
    doOnce([]() { disp->drawOnlyRightBox("NEXT"); });
    disp->blinkTextWithSign("Hello!");
}

void Menu::s1_0() {
    doOnce([]() { disp->drawTwoBoxes("NO", "YES", false); });
    disp->blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s1_1() {
    doOnce([]() { disp->drawTwoBoxes("NO", "YES", true); });
    disp->blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s2() {
    doOnce([]() {
        Pin::setMode(PinMode::SET);
        disp->drawPin(Pin::getPinString());
    });

    disp->blinkTextWithSign("Set pin:");
    nav->enterPin();
}

void Menu::s3() {
    doOnce([]() {
        Pin::setMode(PinMode::CONFIRM);
        disp->drawPin(Pin::getPinString());
    });
    disp->blinkTextWithSign("Confirm pin:");
    nav->enterPin();
}

void Menu::s4_0() {
    doOnce([]() { disp->drawOnlyRightBox("NEXT"); });
    disp->blinkTextWithSign("Pin confirmed!");
}

void Menu::s4_1() {
    doOnce([]() { disp->drawOnlyLeftBox("BACK"); });
    disp->blinkTextWithSign("Pin not matching ;(  try again...");
}

void Menu::s5() {
    doOnce([]() { disp->drawOnlyRightBox("NEXT"); });
    disp->blinkTextWithSign("Now please save your seed phrase!");
}

void Menu::s6_0() {
    doOnce([]() {
        SeedGenerator::setMode(SeedGeneratorMode::SET);
        disp->clearMenu();
        disp->drawOnlyRightBox("NEXT");
        disp->clearText(SCREEN_TEXT_MENU_BORDER_POSITION);
        disp->setTextAtCenter(SeedGenerator::getCurrentWord(), 24);
    });
    disp->blinkTextWithSign(std::to_string(SeedGenerator::currentIndex + 1) + ". word is: ", 20);
    nav->navigateSeed(true);
}

void Menu::s6_1() {
    doOnce([]() {
        disp->drawTwoBoxes("BACK", "NEXT", true);
        disp->clearText(SCREEN_TEXT_MENU_BORDER_POSITION);
        disp->setTextAtCenter(SeedGenerator::getCurrentWord(), 24);
    });
    disp->blinkTextWithSign(std::to_string(SeedGenerator::currentIndex + 1) + ". word is: ", 20);
    nav->navigateSeed(true);
}

void Menu::s6_2() {
    doOnce([]() {
        disp->drawTwoBoxes("BACK", "NEXT", false);
        disp->clearText(SCREEN_TEXT_MENU_BORDER_POSITION);
        disp->setTextAtCenter(SeedGenerator::getCurrentWord(), 24);
    });
    disp->blinkTextWithSign(std::to_string(SeedGenerator::currentIndex + 1) + ". word is: ", 20);
    nav->navigateSeed(false);
}

void Menu::s7() {
    doOnce([]() { disp->drawOnlyRightBox("NEXT"); });
    disp->blinkTextWithSign("Now please confirm your seed.");
}

void Menu::s8_0() {
    doOnce([]() {
        SeedGenerator::setMode(SeedGeneratorMode::CONFIRM);
        disp->drawOnlyRightBox("NEXT");
    });
    disp->blinkTextWithSign("Enter " + std::to_string(SeedGenerator::getCurrentRandom() + 1) + " word:", 20);
    nav->navigateSeed(true);
}

void Menu::s8_1() {
    doOnce([]() { disp->drawTwoBoxes("BACK", "NEXT", true); });
    disp->blinkTextWithSign("Enter " + std::to_string(SeedGenerator::getCurrentRandom() + 1) + " word:", 20);
    nav->navigateSeed(true);
}

void Menu::s8_2() {
    doOnce([]() { disp->drawTwoBoxes("BACK", "NEXT", false); });
    disp->blinkTextWithSign("Enter " + std::to_string(SeedGenerator::getCurrentRandom() + 1) + " word:", 20);
    nav->navigateSeed(false);
}

void Menu::s9_0() {
    doOnce([]() {});
    disp->blinkTextWithSign("Waiting for bluetooth connection...");
}

void Menu::s9_1() {
    doOnce([]() {
        disp->clearMenu();
    });
    disp->blinkTextWithSign("Device connected!   Listening for txs..");
    Bluetooth::sendAddressIfOnConnectedCalled();
    nav->listenTx();
}

void Menu::s9_2() {
    doOnce([]() {
        if(machine.getLastState() != S9_3) {
            disp->clearText(SCREEN_TEXT_MENU_BORDER_POSITION);
        }

        string chainId = Bluetooth::tx->formatChainId();
        string address = Bluetooth::tx->formatAddress();
        string value = Bluetooth::tx->formatEthValue();

        disp->drawTransaction(chainId, address, value);
        disp->drawTwoBoxes("DECLINE", "ACCEPT", false);
    });
}

void Menu::s9_3() {
    doOnce([]() {
        disp->drawTwoBoxes("DECLINE", "ACCEPT", true);
    });
}

void Menu::s9_4() {
    doOnce([]() {
        Bluetooth::signTx();
        disp->drawOnlyLeftBox("BACK");
    });

    disp->blinkTextWithSign("Tx sent!");
}

