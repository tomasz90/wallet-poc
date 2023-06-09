#include <Arduino.h>
#include <sstream>
#include "EthTx.h"
#include "Contract.h"

#define SIGNATURE_LENGTH 64

EthTx::EthTx(std::string &receiverValue) {
    JsonObject &obj = jb.parseObject(receiverValue.c_str());
    if (!obj.success()) {
        Serial.println("parseObject() failed");
        return;
    }
    nonce = obj["nonce"].as<uint32_t>();
    chainId = std::stoull(obj["chainId"].as<char *>());
    gasPrice = std::stoull(obj["gasPrice"].as<char *>());
    gasLimit = obj["gasLimit"].as<uint32_t>();
    destinationAddress = obj["destinationAddress"].as<char *>();
    value = uint256_t(obj["valueHex"].as<char *>());
    data = obj["data"].as<char *>();

}

void EthTx::sign(char *&buffer) {
    JsonObject &obj = jb.createObject();

    Contract contract(chainId);
    contract.SetPrivateKey("0x4c58c5766b922285e8f50fbd5fbd814cabc0b64fabba5bed5800caad6940b520");

    string encoded = contract.SignTransaction(nonce, gasPrice, gasLimit,
                                              &destinationAddress, &value, &data);

    string nonceStr = std::to_string(nonce);
    string chainIdStr = std::to_string(chainId);
    string gasPriceStr = std::to_string(gasPrice);
    string gasLimitStr = std::to_string(gasLimit);
    string valueStr = value.str();

    obj["nonce"] = nonceStr.c_str();
    obj["chainId"] = chainIdStr.c_str();
    obj["gasPrice"] = gasPriceStr.c_str();
    obj["gasLimit"] = gasLimitStr.c_str();;
    obj["destinationAddress"] = destinationAddress.c_str();
    obj["value"] = valueStr.c_str();
    obj["data"] = data.c_str();
    obj["encoded"] = encoded.c_str();

    Serial.println(obj["nonce"].as<char *>());
    Serial.println(obj["chainId"].as<char *>());
    Serial.println(obj["gasPrice"].as<char *>());
    Serial.println(obj["gasLimit"].as<char *>());
    Serial.println(obj["destinationAddress"].as<char *>());
    Serial.println(obj["value"].as<char *>());
    Serial.println(obj["data"].as<char *>());
    Serial.println(obj["encoded"].as<char *>());

    // Get the size of the JSON string
    size_t bufferSize = obj.measureLength() + 1;
    buffer = new char[bufferSize];

    obj.printTo(buffer, bufferSize);
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
