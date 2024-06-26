#ifndef CUSTOMMACHINE_H
#define CUSTOMMACHINE_H

#include "LinkedList.h"
#include "CustomState.h"

class CustomMachine {
public:
    bool executeOnce = true; 	//Indicates that a transition to a different state has occurred

    CustomMachine();
    CustomState* addState(std::function<void()> functionPointer) const;
    CustomState* getLastState() const;
    void run();
    CustomState* transitionTo(CustomState* s);
    int transitionTo(int i);

    int currentState = 0;
private:
    LinkedList<CustomState*> *stateList;
    //Indicates the current state number
    int lastState = 0;
};

#endif //CUSTOMMACHINE_H
