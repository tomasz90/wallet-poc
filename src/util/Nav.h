#ifndef WALLET_POC_NAV_H
#define WALLET_POC_NAV_H

#include <BLEServer.h>
#include "Led.h"
#include "ButtonsHandler.h"
#include "interface/Disp.h"

struct Flag {
    bool flag = false;
    bool check();
    void set();
    void unset();
};

class Nav : public BLEServerCallbacks {
public:
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

    bool deviceConnected = false;
    bool onConnectCalled = false;

    Nav(Led *_led, ButtonsHandler &buttonHandler, Disp *_disp);
    void onPrevious();
    void onNext();
    void onBoth();
    void enterPin();
    void navigateSeed(bool nextHighlighted);
    void readSeedWordFromSerial();
    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);
    void listenTx();
    void sendAddress();

private:
    Led* led;
    Disp *disp;
};

#endif //WALLET_POC_NAV_H
