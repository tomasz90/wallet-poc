#ifndef WALLET_POC_CUSTOMMACHINE_H
#define WALLET_POC_CUSTOMMACHINE_H

#endif //WALLET_POC_CUSTOMMACHINE_H

struct CustomTransition : Transition {
    void (*doOnTransition)();
    CustomTransition(bool (*isTransitioned)(), void (*doOnTransition)(), int stateNumber) {
        this->conditionFunction = isTransitioned;
        this->stateNumber = stateNumber;
        this->doOnTransition = doOnTransition;
    }
};

class CustomState: public State {
public:
    CustomState() = default;
    void addTransition(CustomState *s, bool (*isTransitioned)(), void (*doOnTransition)());
    int evalTransitions() override;

private:
};

