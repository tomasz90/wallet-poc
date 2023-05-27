#include <HardwareSerial.h>
#include "StateMachine.h"
#include "CustomState.h"

void CustomState::addTransition(bool (*isTransitioned)(), void (*doOnTransition)(), CustomState* s) {
    Serial.println("ADD TRANSITION");
    auto t = new CustomTransition{isTransitioned, doOnTransition, s->index};
    transitions->add(t);
}

int CustomState::evalTransitions() {
    // copied all from State, added doOnTransition invocation
    if(transitions->size() == 0) return index;
    bool result = false;
    for(int i=0;i<transitions->size();i++){
        result = transitions->get(i)->conditionFunction();
        if(result == true){
            ((CustomTransition*) transitions->get(i))->doOnTransition();
            return transitions->get(i)->stateNumber;
        }
    }
    return index;
}