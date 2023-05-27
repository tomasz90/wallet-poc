#include "State.h"

#ifndef WALLET_POC_CUSTOMTRANSITION_H
#define WALLET_POC_CUSTOMTRANSITION_H

#endif //WALLET_POC_CUSTOMTRANSITION_H

struct CustomTransition : public Transition {
    CustomTransition(bool (*isTransitioned)(), void (*doOnTransition)(), int stateNumber) : Transition() {
        this->conditionFunction = isTransitioned;
        this->stateNumber = stateNumber;
    }
};