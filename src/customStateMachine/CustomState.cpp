#include <HardwareSerial.h>
#include "StateMachine.h"
#include "CustomState.h"
#include "interface/Disp.h"
#include "interface/Menu.h"
#include "util/Nav.h"

void CustomState::addTransition(
        CustomState *s,
        std::function<bool()> isTrans
) {
    auto t = new CustomTransition{s->index, isTrans, doOnAnyTransition};
    transitions->add(t);
}

void CustomState::doOnAnyTransition() {
    Menu::firstTime = true;
    Disp::lastTextBlinked = 0;
    Nav::nextCalled = false;
    Nav::previousCalled = false;
    Nav::bothCalled = false;
    Nav::nextPinBothCalled = false;
    Nav::previousPinBothCalled = false;
}

int CustomState::evalTransitions() {
    if (transitions->size() == 0) return index;
    for (int i = 0; i < transitions->size(); i++) {
        CustomTransition t = *((CustomTransition *) transitions->get(i));
        if (t.isTrans()) {
            t.doOnTransition();
            return transitions->get(i)->stateNumber;
        }
    }
    return index;
}