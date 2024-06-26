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
    Flag bothCalledWrapped;

    Flag successCalled;
    Flag failureCalled;
    Flag beginCalled;

    Flag resetDeviceCalled;

    Flag btConnectedCalled;
    Flag btDisconnectedCalled;
    Flag receivedTxCalled;

    bool isInit;
    bool executeOnce = true;
    MixedFlag bothCalledAndInit = MixedFlag(bothCalled, isInit);
    MixedFlag bothCalledAndNotInit = MixedFlag(bothCalled, isInit, true);
    DoubleFlag bothCalledAndBtConnected = DoubleFlag(bothCalled, btConnectedCalled);

    bool deviceConnected = false;
    unsigned long connectionTime = 0;

    Nav(Disp* _disp, SeedViewer* _seedViewer, SeedVerifier* _seedVerifier, Repository* _repository, Pin* _pin, Led* led,
        ButtonsHandler &buttonHandler);

    void resetFlags();
    void onPrevious();
    void onNext();
    void onBoth();
    void unlockPin();
    void confirmPin();
    void setPin();
    void viewSeed(bool nextHighlighted);
    void verifySeed(bool nextHighlighted);
    void enterSeed(bool nextHighlighted);
    void checkSerialData();
    void onConnect(BLEServer* pServer) override;
    void onDisconnect(BLEServer* pServer) override;
    void resetBtBuffer();
    void startAdvertising();
    void sendAddress();
    void sendZeroAddress();
    void listenTx();
    void signTx() const;

private:
    Led* led;
    Disp* disp;
    SeedViewer* seedViewer;
    SeedVerifier* seedVerifier;
    Pin* pin;
    Bluetooth* bt;
    Repository* repository;
    Signer* signer;

    void enterPin(bool _bothCalled);
    void checkWords();
};

#endif //NAV_H
