#include <HardwareSerial.h>
#include "StateMachine.h"
#include "CustomState.h"
#include "interface/Disp.h"
#include "interface/Menu.h"
#include "util/Nav.h"

CustomState::CustomState() {
    transitions = new LinkedList<struct CustomTransition *>();
};

void CustomState::addTransition(
        CustomState *s,
        Flag &isTrans
) const {
    auto t = new CustomTransition{s->index, isTrans, doOnAnyTransition};
    transitions->add(t);
}

int CustomState::evalTransitions() const {
    if (transitions->size() == 0) return index;
    for (int i = 0; i < transitions->size(); i++) {
        CustomTransition *t = transitions->get(i);
        if (t->isTrans.check()) {
            t->doOnTransition();
            return transitions->get(i)->stateNumber;
        }
    }
    return index;
}

void CustomState::doOnAnyTransition() {
    Menu::firstTime = true;
    Disp::lastTextBlinked = 0;
    // without this menu is sometimes glitching
    Nav::nextCalled.unset();
    Nav::previousCalled.unset();
    Nav::bothCalled.unset();
    Nav::confirmPinCalled.unset();
    Nav::dropPinCalled.unset();
    Nav::pinMismatchCalled.unset();
}

int CustomState::execute() {
    stateLogic();
    return evalTransitions();
}

int CustomState::setTransition(int index, int stateNo) {
    if (transitions->size() == 0) return -1;
    transitions->get(index)->stateNumber = stateNo;
    return stateNo;
}
