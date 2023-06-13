#ifndef SETUPPINMENU_H
#define SETUPPINMENU_H


#include "AbstractMenu.h"

class SetPinMenu : public AbstractMenu {

public:
    Pin *pin;

    SetPinMenu(CustomMachine *_machine, Nav *_nav, Disp *_disp, Pin *_pin)
    : AbstractMenu(_machine, _nav, _disp) {
        this->pin = _pin;
    }

    void s0() {
        doOnce([this]() { disp->drawTwoBoxes("NO", "YES", false); });
        disp->blinkTextWithSign("Do you want to set as new device?");
    }

    void s1() {
        doOnce([this]() { disp->drawTwoBoxes("NO", "YES", true); });
        disp->blinkTextWithSign("Do you want to set as new device?");
    }

    void s2() {
        doOnce([this]() {
            disp->drawPin(pin->getPinString());
        });

        disp->blinkTextWithSign("Set pin:");
        nav->setPin();
    }

    void s3() {
        doOnce([this]() {
            disp->drawPin(pin->getPinString());
        });
        disp->blinkTextWithSign("Confirm pin:");
        nav->confirmPin();
    }

    void s4() {
        doOnce([this]() { disp->drawOnlyRightBox("NEXT"); });
        disp->blinkTextWithSign("Pin confirmed!");
    }

    void s5() {
        doOnce([this]() { disp->drawOnlyLeftBox("BACK"); });
        disp->blinkTextWithSign("Pin not matching ;(  try again...");
    }
};

#endif //SETUPPINMENU_H
