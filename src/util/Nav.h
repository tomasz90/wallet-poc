#ifndef WALLET_POC_NAV_H
#define WALLET_POC_NAV_H

#include "Led.h"
#include "ButtonsHandler.h"

class Nav {
public:
    static bool previousCalled;
    static bool nextCalled;
    static bool bothCalled;
    static bool nextPinBothCalled;
    static bool previousPinBothCalled;

    static void begin(Led *_led, ButtonsHandler &buttonHandler);
    static void onPrevious();
    static void onNext();
    static void onBoth();
    static void enterPin();

    static std::function<bool()> _(bool &called);

private:
    static Led* led;
};

#endif //WALLET_POC_NAV_H
