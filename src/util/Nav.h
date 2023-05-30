#ifndef WALLET_POC_NAV_H
#define WALLET_POC_NAV_H

#include "Led.h"
#include "ButtonsHandler.h"

struct Flag {
    bool flag = false;
    bool check();
    void set();
    void unset();
};

class Nav {
public:
    static Flag previousCalled;
    static Flag nextCalled;
    static Flag bothCalled;
    static Flag nextPinBothCalled;
    static Flag previousPinBothCalled;

    static void begin(Led *_led, ButtonsHandler &buttonHandler);
    static void onPrevious();
    static void onNext();
    static void onBoth();
    static void enterPin();

private:
    static Led* led;
};

#endif //WALLET_POC_NAV_H
