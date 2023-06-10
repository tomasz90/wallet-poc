#ifndef WALLET_POC_NAV_H
#define WALLET_POC_NAV_H

#include <BLEServer.h>
#include "Led.h"
#include "ButtonsHandler.h"

struct Flag {
    bool flag = false;
    bool check();
    void set();
    void unset();
};

class Nav : public BLEServerCallbacks {
public:
    bool deviceConnected = false;
    bool onConnectCalled = false;
    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);

    Flag previousCalled;
    Flag nextCalled;
    Flag bothCalled;
    Flag confirmPinCalled;
    Flag dropPinCalled;
    Flag pinMismatchCalled;

    Flag firstSeedScreenCalled;
    Flag previousSeedScreenCalled;
    Flag nextSeedScreenCalled;
    Flag confirmSeedScreenCalled;
    Flag isValidWordCalled;

    Flag btConnectedCalled;
    Flag btDisconnectedCalled;
    Flag receivedTxCalled;

    Nav(Led *_led, ButtonsHandler &buttonHandler);
    void onPrevious();
    void onNext();
    void onBoth();
    void enterPin();
    void navigateSeed(bool nextHighlighted);
    void readSeedWordFromSerial();

    void onBtConnected();
    void onBtDisconnected();
    void listenTx();
private:

    Led* led;
};

#endif //WALLET_POC_NAV_H
