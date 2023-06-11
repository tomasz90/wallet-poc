#ifndef NAV_H
#define NAV_H

#include <BLEServer.h>
#include "io/Bluetooth.h"
#include "io/Led.h"
#include "ButtonsHandler.h"
#include "interface/Disp.h"
#include "util/Pin.h"
#include "Flag.h"
#include "seed/SeedViewer.h"
#include "seed/SeedVerifier.h"
#include "io/Signer.h"

class Nav : public BLEServerCallbacks {
public:
    Flag previousCalled;
    Flag nextCalled;
    Flag bothCalled;
    Flag confirmPinCalled;
    Flag dropPinCalled;
    Flag pinMismatchCalled;
    Flag resetDeviceCalled;

    Flag firstSeedScreenCalled;
    Flag previousSeedScreenCalled;
    Flag nextSeedScreenCalled;
    Flag confirmSeedScreenCalled;
    Flag isValidWordCalled;

    Flag btConnectedCalled;
    Flag btDisconnectedCalled;
    Flag receivedTxCalled;

    bool deviceConnected = false;

    Nav(Led *_led,
        ButtonsHandler &buttonHandler,
        Disp *_disp,
        SeedViewer *_seedViewer,
        SeedVerifier *_seedVerifier,
        Repository *_repository,
        Pin *_pin);

    void setBt(Bluetooth *_bt);
    void resetFlags();
    void onPrevious();
    void onNext();
    void onBoth();
    void unlockPin();
    void confirmPin();
    void setPin();
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
    SeedViewer *seedViewer;
    SeedVerifier *seedVerifier;
    Pin *pin;
    Bluetooth *bt;
    Repository *repository;
    Signer *signer;

    void enterPin(bool _bothCalled);
};

#endif //NAV_H
