//
// Created by Tomasz Kulig on 07/06/2023.
//

#ifndef WALLET_POC_BLUETOOTHCALLBACKS_H
#define WALLET_POC_BLUETOOTHCALLBACKS_H


#include <BLEServer.h>

class BluetoothCallbacks : public BLEServerCallbacks {
public:
    bool deviceConnected = false;

    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);
};


#endif //WALLET_POC_BLUETOOTHCALLBACKS_H
