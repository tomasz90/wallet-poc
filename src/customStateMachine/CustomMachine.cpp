#include "StateMachine.h"
#include "CustomMachine.h"

CustomState *CustomMachine::addState(void (*functionPointer)()) {
    CustomState *s = new CustomState();
    s->stateLogic = functionPointer;
    stateList->add(s);
    s->index = stateList->size() - 1;
    return s;
}

CustomState *CustomMachine::getLastState() {
    return (CustomState*) stateList->get(lastState);
}

void CustomMachine::run() {
    if (stateList->size() == 0) return;

    // Initial condition
    if (currentState == -1) {
        currentState = 0;
    }

    int next = stateList->get(currentState)->execute();
    executeOnce = currentState != next;
    if (executeOnce) {
        lastState = currentState;
    }
    currentState = next;
}