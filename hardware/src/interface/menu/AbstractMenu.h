#ifndef ABSTRACTMENU_H
#define ABSTRACTMENU_H

#include "customStateMachine/CustomMachine.h"
#include "interface/Nav.h"

class AbstractMenu {
protected:
    CustomMachine* machine;
    Nav* nav;
    Disp* disp;

    AbstractMenu(CustomMachine* machine, Nav* nav, Disp* disp): machine(machine), nav(nav), disp(disp) {}

    void doOnce(const std::function<void()> &_doOnce) const {
        if (machine->executeOnce) {
            disp->lastTextBlinked = 0;
            nav->resetFlags();
            _doOnce();
        }
    }
};


#endif //ABSTRACTMENU_H
