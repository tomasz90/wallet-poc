#include <HardwareSerial.h>
#include "StateMachine.h"
#include "CustomState.h"

void CustomState::addTransition(bool (*isTransitioned)(), void (*doOnTransition)(), CustomState* s) {
    Serial.println("ADD TRANSITION");
    Transition* t = new Transition{isTransitioned,s->index};
    transitions->add(t);
}

int CustomState::evalTransitions() {
    Serial.println("AEVALUATE");
    return State::evalTransitions();
}