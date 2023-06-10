#ifndef NAV_H
#define NAV_H

#include <BLEServer.h>
#include "io/Bluetooth.h"
#include "io/Led.h"
#include "ButtonsHandler.h"
#include "interface/Disp.h"
#include "util/SeedVerifier.h"
#include "util/Pin.h"
#include "Flag.h"

enum class DataType {
    NONE,
    VALID,
    INVALID
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

    Nav(Led *_led, ButtonsHandler &buttonHandler, Disp *_disp, SeedVerifier *_seedVerifier, Pin *_pin);
    void setBt(Bluetooth *_bt);
    void resetFlags();
    void onPrevious();
    void onNext();
    void onBoth();
    void enterPin();
    void navigateSeed(bool nextHighlighted);
    void navigateSeedConfirm(bool nextHighlighted);
    void checkSerialData();
    void onConnect(BLEServer *pServer) override;
    void onDisconnect(BLEServer *pServer) override;
    void listenTx();
    void sendAddress();
    void signTx() const;

private:
    Led* led;
    Disp *disp;
    SeedVerifier *seedVerifier;
    Pin *pin;
    Bluetooth *bt;

    // this is for Nav purposes only
    Flag btConnectedCalledPrivate;
};

#endif //NAV_H
