#include "CustomState.h"

#ifndef WALLET_POC_CUSTOMMACHINE_H
#define WALLET_POC_CUSTOMMACHINE_H

#endif //WALLET_POC_CUSTOMMACHINE_H

class CustomMachine {
public:
    CustomMachine();
    CustomState* addState(void (*functionPointer)()) const;
    CustomState* getLastState() const;
    void run();

    CustomState* transitionTo(CustomState* s);
    int transitionTo(int i);


private:
    LinkedList<CustomState*> *stateList;
    bool executeOnce = true; 	//Indicates that a transition to a different state has occurred
    int currentState = 0;	//Indicates the current state number
    int lastState = 0;
};

