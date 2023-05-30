#ifndef WALLET_POC_NAV_H
#define WALLET_POC_NAV_H


#include "Led.h"
#include "ButtonsHandler.h"

class Nav {
public:
    static void begin(Led *_led, ButtonsHandler &buttonHandler);
    static void onPrevious();
    static void onNext();
    static void onBoth();

    static bool isPrevious();
    static bool isNext();
    static bool isBoth();

    static void enterPin();
    static bool isNextPin();
    static bool isPreviousPin();
private:
    static Led* led;
    static bool previousCalled;
    static bool nextCalled;
    static bool bothCalled;
    static bool nextPinBothCalled;
    static void resetAll(bool doReset);

    static bool previousPinBothCalled;
};


#endif //WALLET_POC_NAV_H
