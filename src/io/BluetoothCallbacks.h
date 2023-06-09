#ifndef WALLET_POC_BLUETOOTHCALLBACKS_H
#define WALLET_POC_BLUETOOTHCALLBACKS_H

#include <BLEServer.h>

class BluetoothCallbacks : public BLEServerCallbacks {
public:
    bool deviceConnected = false;
    bool onConnectCalled = false;
    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);
};


#endif //WALLET_POC_BLUETOOTHCALLBACKS_H
