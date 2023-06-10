#ifndef CUSTOMSTATE_H
#define CUSTOMSTATE_H

#include <functional>
#include <LinkedList.h>
#include "util/Nav.h"

struct CustomTransition {
    int stateNumber;
    Flag &isTrans;
    void (*doOnTransition)();

    CustomTransition(int stateNumber, Flag &isTrans, void (*doOnTransition)()) : isTrans(isTrans) {
        this->stateNumber = stateNumber;
        this->doOnTransition = doOnTransition;
    }
};

class CustomState {
public:
    int index;
    void (*stateLogic)();

    CustomState();
    void addTransition(CustomState *s, Flag &isTrans) const;
    int evalTransitions() const;
    static void doOnAnyTransition(); //todo remove static?
    int execute();
    int setTransition(int index, int stateNumber);

private:
    LinkedList<struct CustomTransition*> *transitions;
};

#endif //CUSTOMSTATE_H
