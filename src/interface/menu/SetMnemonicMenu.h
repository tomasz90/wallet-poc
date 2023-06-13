#ifndef SETMNEMONICMENU_H
#define SETMNEMONICMENU_H

#include "AbstractMenu.h"

class SetMnemonicMenu : public AbstractMenu {
public:

    Pin *pin;
    Repository *repository;
    SeedViewer *seedViewer;
    SeedVerifier *seedVerifier;

    SetMnemonicMenu(CustomMachine *_machine, Nav *_nav, Disp *_disp, Pin *_pin,
                    Repository *_repository, SeedViewer *_seedViewer, SeedVerifier *_seedVerifier)
            : AbstractMenu(_machine, _nav, _disp) {
        this->pin = _pin;
        this->repository = _repository;
        this->seedViewer = _seedViewer;
        this->seedVerifier = _seedVerifier;
    }
    void s0() {
        doOnce([this]() { disp->drawOnlyRightBox("NEXT"); });
        disp->blinkTextWithSign("Now please save your seed phrase!");
    }

    void s1() {
        doOnce([this]() {
            disp->drawOnlyRightBox("NEXT");
            disp->clearText(SCREEN_TEXT_MENU_BORDER_POSITION);
            disp->setTextAtCenter(seedViewer->getCurrentWord(), 24);
        });
        disp->blinkTextWithSign(std::to_string(seedViewer->currentIndex + 1) + ". word is: ", 20);
        nav->viewSeed(true);
    }

    void s2() {
        doOnce([this]() {
            disp->drawTwoBoxes("BACK", "NEXT", true);
        });
        disp->blinkTextWithSign(std::to_string(seedViewer->currentIndex + 1) + ". word is: ", 20);
        nav->viewSeed(true);
    }

    void s3() {
        doOnce([this]() {
            disp->drawTwoBoxes("BACK", "NEXT", false);
        });
        disp->blinkTextWithSign(std::to_string(seedViewer->currentIndex + 1) + ". word is: ", 20);
        nav->viewSeed(false);
    }

    void s4() {
        doOnce([this]() {
            disp->clearMenu();
            nav->resetBtBuffer();
            //todo: this should be done right after connection
            nav->notifyUninitializedDevice();
        });

        // todo: resolve this problem:

        //    doOnce([this]() {
        //        disp->drawOnlyRightBox("NEXT");
        //    }, nav->deviceConnected);

        disp->blinkTextWithSign("Now please confirm  your seed. Connect with your browser.");
    }

    void s5() {
        doOnce([this]() {
            disp->clearTextCenter();
            disp->drawOnlyRightBox("NEXT");
        });
        disp->blinkTextWithSign("Enter " + std::to_string(seedVerifier->getCurrentRandom() + 1) + " word:",
                                22); // todo: introduce some const for 22
        nav->verifySeed(true);
    }

    void s6() {
        doOnce([this]() { disp->drawTwoBoxes("BACK", "NEXT", true); });
        disp->blinkTextWithSign("Enter " + std::to_string(seedVerifier->getCurrentRandom() + 1) + " word:", 20);
        nav->verifySeed(true);
    }

    void s7() {
        doOnce([this]() { disp->drawTwoBoxes("BACK", "NEXT", false); });
        disp->blinkTextWithSign("Enter " + std::to_string(seedVerifier->getCurrentRandom() + 1) + " word:", 20);
        nav->verifySeed(false);
    }
};

#endif //SETMNEMONICMENU_H
