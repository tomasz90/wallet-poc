#include <HardwareSerial.h>
#include "StateMachine.h"
#include "CustomState.h"

CustomState::CustomState() {
    transitions = new LinkedList<struct CustomTransition *>();
};

void CustomState::addTransition(
        CustomState *s,
        Flag &isTrans
) const {
    auto t = new CustomTransition(s->index, isTrans);
    transitions->add(t);
}

int CustomState::evalTransitions() const {
    if (transitions->size() == 0) return index;
    for (int i = 0; i < transitions->size(); i++) {
        CustomTransition *t = transitions->get(i);
        if (t->isTrans.check()) {
            return transitions->get(i)->stateNumber;
        }
    }
    return index;
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
