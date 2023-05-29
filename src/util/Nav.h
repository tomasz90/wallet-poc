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

    static bool isPreviousCalled();
    static bool isNextCalled();
    static bool isBothCalled();

    static void enterPin(int position);
    static bool isNextForPin();
    static bool isPreviousForPin();
private:
    static Led* led;
    static bool previousCalled;
    static bool nextCalled;
    static bool bothCalled;
};


#endif //WALLET_POC_NAV_H
