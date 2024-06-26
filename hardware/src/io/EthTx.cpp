#include <Arduino.h>
#include <sstream>
#include "EthTx.h"

#define SIGNATURE_LENGTH 64

EthTx::EthTx(std::string &receiverValue) {
    JsonObject &obj = jb.parseObject(receiverValue.c_str());
    if (!obj.success()) {
        Serial.println("parseObject() failed");
        return;
    }
    nonce = obj["nonce"].as<uint32_t>();
    chainId = std::stoull(obj["chainId"].as<char* >());
    gasPrice = std::stoull(obj["gasPrice"].as<char* >());
    gasLimit = obj["gasLimit"].as<uint32_t>();
    destinationAddress = obj["destinationAddress"].as<char* >();
    value = uint256_t(obj["valueHex"].as<char* >());
    data = obj["data"].as<char* >();

}

std::string EthTx::formatChainId() const {
    return std::to_string(chainId);
}

std::string EthTx::formatAddress() const {
    std::string address = destinationAddress;
    address.replace(6, 30, "...");
    return address;
}

std::string EthTx::formatEthValue() const {
    std::string valueStr = value.str();
    uint8_t length = valueStr.length();
    if (length < 19) {
        uint8_t countZeros = 18 - length;
        valueStr.insert(0, "0.");
        valueStr.insert(2, countZeros, '0');
    } else {
        valueStr.insert(length - 18, ".");
    }

    uint8_t index = valueStr.length() - 1;
    while (valueStr[index] == '0') {
        valueStr.erase(index, 1);
        index--;
    }

    if (valueStr.back() == '.') {
        valueStr.pop_back();
    }
    return valueStr;
}
