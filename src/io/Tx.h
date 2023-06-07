//
// Created by Tomasz Kulig on 07/06/2023.
//

#ifndef BLE_POC_TX_H
#define BLE_POC_TX_H


#include <cstdint>
#include <string>
#include <ArduinoJson.h>

class Tx {

public:
    uint32_t nonce;
    std::string gasPrice;
    uint32_t gasLimit;
    std::string destinationAddress;
    std::string value;
    std::string data;

    DynamicJsonBuffer jb;

    Tx();

    explicit Tx(std::string &receiverValue);

    void serialize(char *&buffer);
};


#endif //BLE_POC_TX_H
