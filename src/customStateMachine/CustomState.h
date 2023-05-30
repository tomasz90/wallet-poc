#ifndef WALLET_POC_CUSTOMMACHINE_H
#define WALLET_POC_CUSTOMMACHINE_H

#endif //WALLET_POC_CUSTOMMACHINE_H

struct CustomTransition : Transition {
    void (*doOnTransition)();

    CustomTransition(int s, bool (*isTrans)(), void (*doOnTransition)()) : Transition() {
        this->stateNumber = s;
        this->conditionFunction = isTrans;
        this->doOnTransition = doOnTransition;
    }
};

class CustomState : public State {
public:
    CustomState() = default;
    void addTransition(CustomState *s, bool (*isTrans)());
    int evalTransitions() override;

    static void doOnAnyTransition();
};

