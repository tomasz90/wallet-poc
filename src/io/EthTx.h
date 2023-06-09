#ifndef BLE_POC_TX_H
#define BLE_POC_TX_H


#include <cstdint>
#include <string>
#include <ArduinoJson.h>
#include "uint256/uint256_t.h"

class EthTx {

public:
    uint32_t nonce;
    unsigned long long chainId;
    unsigned long long gasPrice;
    uint32_t gasLimit;
    std::string destinationAddress;
    uint256_t value;
    std::string data;

    explicit EthTx(std::string &receiverValue);
    void sign(char *&buffer);
    std::string getEthValue() const;
private:
    DynamicJsonBuffer jb;
};


#endif //BLE_POC_TX_H
