#ifndef WALLET_POC_CUSTOMMACHINE_H
#define WALLET_POC_CUSTOMMACHINE_H

#endif //WALLET_POC_CUSTOMMACHINE_H

struct CustomTransition{
    bool (*isTransitioned)();
    void (*doOnTransition)();
    int stateNumber;
};

class CustomState: public State {
public:
    //LinkedList<struct CustomTransition*> *transitions;
    CustomState() = default;
    void addTransition(bool (*isTransitioned)(), void (*doOnTransition)(), CustomState* s);
    int evalTransitions();

private:
};

