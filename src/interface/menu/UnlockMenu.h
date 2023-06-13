#ifndef UNLOCKMENU_H
#define UNLOCKMENU_H

#include "util/Repository.h"
#include "AbstractMenu.h"

class UnlockMenu : public AbstractMenu {

public:
    Pin* pin;
    Repository* repository;

    UnlockMenu(CustomMachine* machine, Nav* nav, Disp* disp, Pin* pin, Repository* repository)
            : AbstractMenu(machine, nav, disp), pin(pin), repository(repository) {}

    void s0() {
        doOnce([this]() {
            disp->drawOnlyRightBox("NEXT");
            nav->isInit = repository->isInitialized();
        });
        disp->blinkTextWithSign("Hello!");
    }

    void s1() {
        doOnce([this]() {
            disp->drawPin(pin->getPinString());
        });
        disp->blinkTextWithSign("Enter pin:");
        nav->unlockPin();
    }

    void s2() {
        doOnce([this]() {
            disp->drawOnlyLeftBox("BACK");
            disp->setTextAtCenter(("Left tries: " + String(repository->getLeftTries())).c_str(), 24);
        });
        disp->blinkTextWithSign("Pin not matching.", 20);
    }

    void s3() {
        doOnce([this]() {
            disp->drawOnlyLeftBox("BACK");
        });
        disp->blinkTextWithSign("Device was reset.");
    }
};


#endif //UNLOCKMENU_H
