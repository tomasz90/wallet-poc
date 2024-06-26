#include "StateMachine.h"
#include "CustomMachine.h"

#include <utility>

CustomMachine::CustomMachine() {
    stateList = new LinkedList<CustomState*>();
};

CustomState *CustomMachine::addState(std::function<void()> functionPointer) const {
    auto *s = new CustomState();
    s->stateLogic = std::move(functionPointer);
    stateList->add(s);
    s->index = stateList->size() - 1;
    return s;
}

CustomState *CustomMachine::getLastState() const {
    return (CustomState*) stateList->get(lastState);
}

void CustomMachine::run() {
    if (stateList->size() == 0) return;

    int initialState = currentState;
    int next = stateList->get(currentState)->execute();
    if (initialState == currentState) {
        executeOnce = currentState != next;
        currentState = next;
    }
}


CustomState* CustomMachine::transitionTo(CustomState* s){
    this->currentState = s->index;
    this->executeOnce = true;
    return s;
}

int CustomMachine::transitionTo(int i){
    if(i < stateList->size()){
        this->currentState = i;
        this->executeOnce = true;
        return i;
    }
    return currentState;
}