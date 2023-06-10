#ifndef BLE_POC_TX_H
#define BLE_POC_TX_H


#include <cstdint>
#include <string>
#include <ArduinoJson.h>
#include "uint256/uint256_t.h"

class EthTx {

public:
    explicit EthTx(std::string &receiverValue);

    void sign(char *&buffer, const char *key);
    std::string formatChainId() const;
    std::string formatAddress() const;
    std::string formatEthValue() const;
private:
    DynamicJsonBuffer jb;

    uint32_t nonce;
    unsigned long long chainId;
    unsigned long long gasPrice;
    uint32_t gasLimit;
    std::string destinationAddress;
    uint256_t value;
    std::string data;
};


#endif //BLE_POC_TX_H
