#include "CustomState.h"

#ifndef WALLET_POC_CUSTOMMACHINE_H
#define WALLET_POC_CUSTOMMACHINE_H

#endif //WALLET_POC_CUSTOMMACHINE_H

class CustomMachine: public StateMachine {
public:
    CustomMachine() = default;
    CustomState* addState(void (*functionPointer)()) override;

private:
};

