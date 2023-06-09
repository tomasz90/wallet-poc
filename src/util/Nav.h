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
    static Flag confirmPinCalled;
    static Flag dropPinCalled;
    static Flag pinMismatchCalled;

    static Flag firstSeedScreenCalled;
    static Flag previousSeedScreenCalled;
    static Flag nextSeedScreenCalled;
    static Flag confirmSeedScreenCalled;
    static Flag isValidWordCalled;

    static Flag btConnectedCalled;
    static Flag btDisconnectedCalled;
    static Flag receivedTxCalled;

    static void begin(Led *_led, ButtonsHandler &buttonHandler);
    static void onPrevious();
    static void onNext();
    static void onBoth();
    static void enterPin();
    static void navigateSeed(bool nextHighlighted);
    static void readSeedWordFromSerial();

    static void onBtConnected();
    static void onBtDisconnected();
    static void listenTx();
private:

    static Led* led;
};

#endif //WALLET_POC_NAV_H
