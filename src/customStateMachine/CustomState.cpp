#include <HardwareSerial.h>
#include "StateMachine.h"
#include "CustomState.h"
#include "interface/Disp.h"
#include "interface/Menu.h"
#include "util/Nav.h"

void CustomState::addTransition(
        CustomState *s,
        Flag &isTrans
) {
    auto t = new CustomTransition{s->index, isTrans, doOnAnyTransition};
    transitions->add(t);
}

void CustomState::doOnAnyTransition() {
    Menu::firstTime = true;
    Disp::lastTextBlinked = 0;
    // without this menu is sometimes glitching
    Nav::nextCalled.unset();
    Nav::previousCalled.unset();
    Nav::bothCalled.unset();
    Nav::nextPinBothCalled.unset();
    Nav::previousPinBothCalled.unset();
    Nav::pinMismatch.unset();
}

int CustomState::evalTransitions() {
    if (transitions->size() == 0) return index;
    for (int i = 0; i < transitions->size(); i++) {
        CustomTransition t = *((CustomTransition *) transitions->get(i));
        if (t.isTrans.check()) {
            t.doOnTransition();
            return transitions->get(i)->stateNumber;
        }
    }
    return index;
}