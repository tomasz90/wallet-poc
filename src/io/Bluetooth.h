#ifndef WALLET_POC_BLUETOOTH_H
#define WALLET_POC_BLUETOOTH_H

#include "EthTx.h"

// SERVICES
#define SERVICE_ADDRESS_UUID  "b39418c1-5b51-4828-a8a0-7ee0eef01dba"
#define SERVICE_UUID          "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

// CHARACTERISTICS
#define SENDER_ADDRESS_UUID   "6a079629-af17-4a50-bda7-80d55196dd27"
#define SENDER_UUID           "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define RECEIVER_UUID         "03d2fde6-1615-461d-897b-6b0220bdd335"

class Bluetooth {
public:
    EthTx* tx;
    Bluetooth(BLEServerCallbacks *_nav);
    void sendAddress();
    bool receivedTx();
    void signTx();
    void declineTx();
};

#endif //WALLET_POC_BLUETOOTH_H
