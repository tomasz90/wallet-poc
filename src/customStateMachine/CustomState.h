#ifndef CUSTOMSTATE_H
#define CUSTOMSTATE_H

#include <functional>
#include <LinkedList.h>
#include "util/Nav.h"

struct CustomTransition {
    int stateNumber;
    Flag &isTrans;

    CustomTransition(int stateNumber, Flag &isTrans) : isTrans(isTrans) {
        this->stateNumber = stateNumber;
    }
};

class CustomState {
public:
    int index;
    void (*stateLogic)();

    CustomState();
    void addTransition(CustomState *s, Flag &isTrans) const;
    int evalTransitions() const;
    int execute();
    int setTransition(int index, int stateNumber);

private:
    LinkedList<struct CustomTransition*> *transitions;
};

#endif //CUSTOMSTATE_H
