#include <HardwareSerial.h>
#include "StateMachine.h"
#include "CustomState.h"
#include "interface/Disp.h"
#include "interface/Menu.h"

void CustomState::addTransition(
        CustomState *s,
        bool (*isTrans)()
) {
    auto t = new CustomTransition{s->index, isTrans, doOnAnyTransition};
    transitions->add(t);
}

void CustomState::doOnAnyTransition() {
    Menu::firstTime = true;
    Disp::lastTextBlinked = 0;
}

int CustomState::evalTransitions() {
    if (transitions->size() == 0) return index;
    for (int i = 0; i < transitions->size(); i++) {
        CustomTransition t = *((CustomTransition *) transitions->get(i));
        if (t.conditionFunction()) {
            t.doOnTransition();
            return transitions->get(i)->stateNumber;
        }
    }
    return index;
}