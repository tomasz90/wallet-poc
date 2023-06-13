#ifndef UNLOCKMENU_H
#define UNLOCKMENU_H

#include "util/Repository.h"
#include "AbstractMenu.h"

class UnlockMenu : public AbstractMenu {

public:
    Pin *pin;
    Repository *repository;

    UnlockMenu(CustomMachine *_machine, Nav *_nav, Disp *_disp, Pin *_pin, Repository *_repository)
            : AbstractMenu(_machine, _nav, _disp) {
        this->pin = _pin;
        this->repository = _repository;
    }

    void s0() {
        doOnce([this]() {
            disp->drawOnlyRightBox("NEXT");
            nav->isInit = repository->isInitialized();
        });
        disp->blinkTextWithSign("Hello!");
    }

    void s1_0_() {
        doOnce([this]() {
            disp->drawPin(pin->getPinString());
        });
        disp->blinkTextWithSign("Enter pin:");
        nav->unlockPin();
    }

    void s1_1_() {
        doOnce([this]() {
            disp->drawOnlyLeftBox("BACK");
            disp->setTextAtCenter(("Left tries: " + String(repository->getLeftTries())).c_str(), 24);
        });
        disp->blinkTextWithSign("Pin not matching.", 20);
    }

    void s1_2_() {
        doOnce([this]() {
            disp->drawOnlyLeftBox("BACK");
        });
        disp->blinkTextWithSign("Device was reset.");
    }
};


#endif //UNLOCKMENU_H
