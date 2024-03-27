#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "EthTx.h"
#include "util/Repository.h"

class Bluetooth {
public:
    Bluetooth(BLEServerCallbacks *nav);
    void startAdvertising();
    void sendAddress(const string &address);
    void resetBuffer();
    string receiveData();
    void sendTx(char *buffer);
};

#endif //BLUETOOTH_H
