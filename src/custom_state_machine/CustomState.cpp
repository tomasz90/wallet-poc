#include <HardwareSerial.h>
#include "StateMachine.h"
#include "CustomState.h"
#include "util/display.h"
#include "util/menu.h"

// doFirst can display static content that don't need to be updated
void CustomState::addTransition(
        CustomState *s,
        bool (*isTrans)(),
        void (*doFirst)(),
        void (*doSecond)()
) {
    auto t = new CustomTransition{s->index, isTrans, doFirst, doSecond};
    transitions->add(t);
}

void CustomState::addTransition(
        CustomState *s,
        bool (*isTrans)(),
        void (*doFirst)()
) {
    addTransition(s, isTrans, anyTransition, doFirst);
}

void CustomState::anyTransition() {
    Disp::firstTime = true;
}

int CustomState::evalTransitions() {
    if (transitions->size() == 0) return index;
    for (int i = 0; i < transitions->size(); i++) {
        CustomTransition t = *((CustomTransition *) transitions->get(i));
        if (t.conditionFunction()) {
            t.doFirst();
            if (t.doSecond != nullptr) t.doSecond();
            return transitions->get(i)->stateNumber;
        }
    }
    return index;
}