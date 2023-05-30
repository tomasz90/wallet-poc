#ifndef WALLET_POC_CUSTOMMACHINE_H
#define WALLET_POC_CUSTOMMACHINE_H
#endif //WALLET_POC_CUSTOMMACHINE_H

#include <functional>
#include "util/Nav.h"

struct CustomTransition : Transition {
    void (*doOnTransition)();
    Flag &isTrans;

    CustomTransition(int s, Flag &isTrans, void (*doOnTransition)()) : Transition(), isTrans(isTrans) {
        this->stateNumber = s;
        // todo: transition to your own solution entirely
        this->conditionFunction = [] { return false; };
        this->doOnTransition = doOnTransition;
    }
};

class CustomState : public State {
public:
    CustomState() = default;
    void addTransition(CustomState *s, Flag &isTrans);
    int evalTransitions() override;

    static void doOnAnyTransition();
};

