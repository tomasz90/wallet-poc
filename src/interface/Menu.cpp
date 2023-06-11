#include "Menu.h"
#include "customStateMachine/CustomMachine.h"
#include "ButtonsHandler.h"
#include "Nav.h"
#include "seed/SeedVerifier.h"
#include "io/Bluetooth.h"

CustomMachine machine = CustomMachine();

CustomState *S9_3 = nullptr;

using std::string;

CustomState *S1_0 = nullptr;
CustomState *S1_0_ = nullptr;

Menu::Menu(Nav *_nav, Disp *_disp, SeedViewer *_seedViewer, SeedVerifier *_seedVerifier, Repository *_repository,
           Pin *_pin) {
    nav = _nav;
    disp = _disp;
    seedViewer = _seedViewer;
    seedVerifier = _seedVerifier;
    pin = _pin;
    repository = _repository;

    // STATES
    CustomState *S0 =   machine.addState([this]() { s0();});
    S1_0 = machine.addState([this]() { s1_0();});
    S1_0_ = machine.addState([this]() { s1_0_();});
    CustomState *S1_1_ = machine.addState([this]() { s1_1_();});
    CustomState *S1_2_ = machine.addState([this]() { s1_2_();});
    CustomState *S1_1 = machine.addState([this]() { s1_1();});
    CustomState *S2 =   machine.addState([this]() { s2();});
    CustomState *S3 =   machine.addState([this]() { s3();});
    CustomState *S4_0 = machine.addState([this]() { s4_0();});
    CustomState *S4_1 = machine.addState([this]() { s4_1();});
    CustomState *S5 =   machine.addState([this]() { s5();});
    CustomState *S6_0 = machine.addState([this]() { s6_0();});
    CustomState *S6_1 = machine.addState([this]() { s6_1();});
    CustomState *S6_2 = machine.addState([this]() { s6_2();});
    CustomState *S7 =   machine.addState([this]() { s7();});
    CustomState *S8_0 = machine.addState([this]() { s8_0(); });
    CustomState *S8_1 = machine.addState([this]() { s8_1(); });
    CustomState *S8_2 = machine.addState([this]() { s8_2(); });
    CustomState *S9_0 = machine.addState([this]() { s9_0(); });
    CustomState *S9_1 = machine.addState([this]() { s9_1(); });
    CustomState *S9_2 = machine.addState([this]() { s9_2(); });
    S9_3 = machine.addState([this]() { s9_3(); });
    CustomState *S9_4 = machine.addState([this]() { s9_4(); });

    // NEXT
    S1_0_->addTransition(S1_1_,nav->pinMismatchCalled);
    S1_0_->addTransition(S1_2_,nav->resetDeviceCalled);
    S1_0_->addTransition(S9_0,nav->confirmPinCalled);
    S1_1_->addTransition(S1_0_,nav->bothCalled);
    S1_2_->addTransition(S0,nav->bothCalled);
    S1_0->addTransition(S1_1,nav->nextCalled);
    S1_1->addTransition(S2,  nav->bothCalled);
    S2->addTransition(S3,    nav->confirmPinCalled);
    S3->addTransition(S4_0,  nav->confirmPinCalled);
    S3->addTransition(S4_1,  nav->pinMismatchCalled);
    S4_0->addTransition(S5,  nav->bothCalled);
    S4_1->addTransition(S2,  nav->bothCalled);

    S9_0->addTransition(S9_1, nav->btConnectedCalled);
    S9_1->addTransition(S9_2, nav->receivedTxCalled);
    S9_2->addTransition(S9_3, nav->nextCalled);
    S9_3->addTransition(S9_4, nav->bothCalled);

    // PREVIOUS
    S1_1->addTransition(S1_0,nav->previousCalled);
    S2->addTransition(S1_0,  nav->dropPinCalled);
    S3->addTransition(S2,    nav->dropPinCalled);

    S5->addTransition(S6_0,    nav->bothCalled);
    S6_0->addTransition(S6_1,nav->nextSeedScreenCalled);
    S6_1->addTransition(S6_2,nav->previousCalled);
    S6_2->addTransition(S6_1,nav->nextCalled);
    S6_1->addTransition(S7,  nav->confirmSeedScreenCalled);
    S6_2->addTransition(S6_0,nav->firstSeedScreenCalled);
    S7->addTransition(S8_0,  nav->bothCalled);
    S8_0->addTransition(S8_1, nav->nextSeedScreenCalled); //todo: change to generic wrapper of next and previous
    S8_1->addTransition(S8_2, nav->previousCalled);
    S8_1->addTransition(S9_0, nav->confirmSeedScreenCalled);
    S8_2->addTransition(S8_1, nav->nextCalled);
    S8_2->addTransition(S8_0, nav->firstSeedScreenCalled);

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

void Menu::doOnce(const std::function<void()> &_doOnce) {
    if (machine.executeOnce) {
        disp->lastTextBlinked = 0;
        nav->resetFlags();
        _doOnce();
    }
}

void Menu::s0() {
    doOnce([this]() { disp->drawOnlyRightBox("NEXT"); });
    disp->blinkTextWithSign("Hello!");
    if(nav->bothCalled.check()) {
        if(repository->isInitialized()) {
            machine.transitionTo(S1_0_);
        } else {
            machine.transitionTo(S1_0);
        }
    }
}

void Menu::s1_0_() {
    doOnce([this]() {
        disp->drawPin(pin->getPinString());
    });
    disp->blinkTextWithSign("Enter pin:");
    nav->unlockPin();
}

void Menu::s1_1_() {
    doOnce([this]() {
        disp->drawOnlyLeftBox("BACK");
        disp->setTextAtCenter(("Left tries: " + String(repository->getLeftTries())).c_str(), 24);
    });
    disp->blinkTextWithSign("Pin not matching.", 20);
}

void Menu::s1_2_() {
    doOnce([this]() {
        disp->drawOnlyLeftBox("BACK");
    });
    disp->blinkTextWithSign("Device was reset.");
}

void Menu::s1_0() {
    doOnce([this]() { disp->drawTwoBoxes("NO", "YES", false); });
    disp->blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s1_1() {
    doOnce([this]() { disp->drawTwoBoxes("NO", "YES", true); });
    disp->blinkTextWithSign("Do you want to set as new device?");
}

void Menu::s2() {
    doOnce([this]() {
        disp->drawPin(pin->getPinString());
    });

    disp->blinkTextWithSign("Set pin:");
    nav->setPin();
}

void Menu::s3() {
    doOnce([this]() {
        disp->drawPin(pin->getPinString());
    });
    disp->blinkTextWithSign("Confirm pin:");
    nav->confirmPin();
}

void Menu::s4_0() {
    doOnce([this]() { disp->drawOnlyRightBox("NEXT"); });
    disp->blinkTextWithSign("Pin confirmed!");
}

void Menu::s4_1() {
    doOnce([this]() { disp->drawOnlyLeftBox("BACK"); });
    disp->blinkTextWithSign("Pin not matching ;(  try again...");
}

void Menu::s5() {
    doOnce([this]() { disp->drawOnlyRightBox("NEXT"); });
    disp->blinkTextWithSign("Now please save your seed phrase!");
}

void Menu::s6_0() {
    doOnce([this]() {
        disp->clearMenu();
        disp->drawOnlyRightBox("NEXT");
        disp->clearText(SCREEN_TEXT_MENU_BORDER_POSITION);
        disp->setTextAtCenter(seedViewer->getCurrentWord(), 24);
    });
    disp->blinkTextWithSign(std::to_string(seedViewer->currentIndex + 1) + ". word is: ", 20);
    nav->navigateSeed(true);
}

void Menu::s6_1() {
    doOnce([this]() {
        disp->drawTwoBoxes("BACK", "NEXT", true);
    });
    disp->blinkTextWithSign(std::to_string(seedViewer->currentIndex + 1) + ". word is: ", 20);
    nav->navigateSeed(true);
}

void Menu::s6_2() {
    doOnce([this]() {
        disp->drawTwoBoxes("BACK", "NEXT", false);
    });
    disp->blinkTextWithSign(std::to_string(seedVerifier->currentIndex + 1) + ". word is: ", 20);
    nav->navigateSeed(false);
}

void Menu::s7() {
    doOnce([this]() { disp->drawOnlyRightBox("NEXT"); });
    disp->blinkTextWithSign("Now please confirm your seed.");
}

void Menu::s8_0() {
    doOnce([this]() {
        disp->drawOnlyRightBox("NEXT");
    });
    disp->blinkTextWithSign("Enter " + std::to_string(seedVerifier->getCurrentRandom() + 1) + " word:", 20);
    nav->navigateSeedConfirm(true);
}

void Menu::s8_1() {
    doOnce([this]() { disp->drawTwoBoxes("BACK", "NEXT", true); });
    disp->blinkTextWithSign("Enter " + std::to_string(seedVerifier->getCurrentRandom() + 1) + " word:", 20);
    nav->navigateSeedConfirm(true);
}

void Menu::s8_2() {
    doOnce([this]() { disp->drawTwoBoxes("BACK", "NEXT", false); });
    disp->blinkTextWithSign("Enter " + std::to_string(seedVerifier->getCurrentRandom() + 1) + " word:", 20);
    nav->navigateSeedConfirm(false);
}

void Menu::s9_0() {
    doOnce([this]() { disp->clearMenu(); });
    disp->blinkTextWithSign("Waiting for bluetooth connection...");
}

void Menu::s9_1() {
    doOnce([this]() {
        disp->clearMenu();
        nav->sendAddress();
    });
    disp->blinkTextWithSign("Device connected!   Listening for txs..");
    nav->listenTx();
}

void Menu::s9_2() {
    doOnce([this]() {
        if (machine.getLastState() != S9_3) {
            disp->clearText(SCREEN_TEXT_MENU_BORDER_POSITION);
        }

        string chainId = repository->tx->formatChainId();
        string address = repository->tx->formatAddress();
        string value = repository->tx->formatEthValue();

        disp->drawTransaction(chainId, address, value);
        disp->drawTwoBoxes("DECLINE", "ACCEPT", false);
    });
}

void Menu::s9_3() {
    doOnce([this]() {
        disp->drawTwoBoxes("DECLINE", "ACCEPT", true);
    });
}

void Menu::s9_4() {
    doOnce([this]() {
        nav->signTx();
        disp->drawOnlyLeftBox("BACK");
    });

    disp->blinkTextWithSign("Tx sent!");
}

