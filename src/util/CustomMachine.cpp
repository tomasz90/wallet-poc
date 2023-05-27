#include "StateMachine.h"
#include "CustomMachine.h"

CustomState *CustomMachine::addState(void (*functionPointer)()) {
    CustomState* s = new CustomState();
    s->stateLogic = functionPointer;
    stateList->add(s);
    s->index = stateList->size()-1;
    return s;
}