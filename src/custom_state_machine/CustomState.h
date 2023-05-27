#ifndef WALLET_POC_CUSTOMMACHINE_H
#define WALLET_POC_CUSTOMMACHINE_H

#endif //WALLET_POC_CUSTOMMACHINE_H

struct CustomTransition : Transition {
    void (*doFirst)();
    void (*doSecond)();

    CustomTransition(int s, bool (*isTrans)(), void (*doFirst)(), void (*doSecond)() = nullptr) : Transition() {
        this->stateNumber = s;
        this->conditionFunction = isTrans;
        this->doFirst = doFirst;
        this->doSecond = doSecond;
    }
};

class CustomState : public State {
public:
    CustomState() = default;
    void addTransition(CustomState *s, bool (*isTrans)(), void (*doFirst)(), void (*doSecond)());
    void addTransition(CustomState *s, bool (*isTrans)(), void (*doSecond)() = nullptr);
    int evalTransitions() override;
};

