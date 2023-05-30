#ifndef WALLET_POC_CUSTOMMACHINE_H
#define WALLET_POC_CUSTOMMACHINE_H
#endif //WALLET_POC_CUSTOMMACHINE_H

#include <functional>

struct CustomTransition : Transition {
    void (*doOnTransition)();
    std::function<bool()> isTrans;

    CustomTransition(int s, std::function<bool()> &isTrans, void (*doOnTransition)()) : Transition() {
        this->stateNumber = s;
        this->conditionFunction = [] { return false; };
        this->doOnTransition = doOnTransition;
        this->isTrans = isTrans;
    }
};

class CustomState : public State {
public:
    CustomState() = default;
    void addTransition(CustomState *s, std::function<bool()> isTrans);
    int evalTransitions() override;

    static void doOnAnyTransition();
};

