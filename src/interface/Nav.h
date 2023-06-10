#ifndef WALLET_POC_NAV_H
#define WALLET_POC_NAV_H

#include <BLEServer.h>
#include "io/Bluetooth.h"
#include "io/Led.h"
#include "ButtonsHandler.h"
#include "interface/Disp.h"
#include "util/SeedGenerator.h"
#include "util/Pin.h"
#include "Flag.h"

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

    Nav(Led *_led, ButtonsHandler &buttonHandler, Disp *_disp, SeedGenerator *_seedGenerator, Pin *_pin);
    void setBt(Bluetooth *_bt);
    void resetFlags();
    void onPrevious();
    void onNext();
    void onBoth();
    void enterPin();
    void navigateSeed(bool nextHighlighted);
    void readSeedWordFromSerial();
    void onConnect(BLEServer *pServer) override;
    void onDisconnect(BLEServer *pServer) override;
    void listenTx();
    void sendAddress();
    void signTx() const;

private:
    Led* led;
    Disp *disp;
    SeedGenerator *seedGenerator;
    Pin *pin;
    Bluetooth *bt;

    // this is for Nav purposes only
    Flag btConnectedCalledPrivate;
};

#endif //WALLET_POC_NAV_H
