#ifndef BLE_POC_TX_H
#define BLE_POC_TX_H


#include <cstdint>
#include <string>
#include <ArduinoJson.h>
#include "uint256/uint256_t.h"

class Tx {

public:
    uint32_t nonce;
    unsigned long long gasPrice;
    uint32_t gasLimit;
    std::string destinationAddress;
    std::string value;
    std::string data;

    DynamicJsonBuffer jb;

    Tx();

    explicit Tx(std::string &receiverValue);

    void sign(char *&buffer);
};


#endif //BLE_POC_TX_H
