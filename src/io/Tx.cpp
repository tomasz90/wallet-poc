#include <Arduino.h>
#include <sstream>
#include "Tx.h"
#include "Contract.h"

#define SIGNATURE_LENGTH 64

Tx::Tx() {}

Tx::Tx(std::string &receiverValue) {
    JsonObject &obj = jb.parseObject(receiverValue.c_str());
    if (!obj.success()) {
        Serial.println("parseObject() failed");
        return;
    }
    nonce = obj["nonce"];
    gasPrice = std::stoull(obj["gasPrice"].as<char *>());
    gasLimit = obj["gasLimit"];
    destinationAddress = obj["destinationAddress"].as<char *>();
    value = toUint256(obj["value"].as<char *>());
    data = obj["data"].as<char *>();

    Serial.println(value.str().c_str());
}

void Tx::sign(char *&buffer) {
    JsonObject &obj = jb.createObject();

//    uint8_t signature[SIGNATURE_LENGTH];
//    memset(signature, 0, SIGNATURE_LENGTH);
//    int recid[1] = {0};
//    auto contract = new Contract();
//    contract->GenerateSignature(signature, recid, nonce, gasPrice, gasLimit,
//                      &destinationAddress, &value, &data);

    obj["nonce"] = nonce;
    obj["gasPrice"] = std::to_string(gasPrice).c_str();
    obj["gasLimit"] = gasLimit;
    obj["destinationAddress"] = destinationAddress.c_str();
    obj["value"] = value.str().c_str();
    obj["data"] = data.c_str();
    obj["signature"] = "signature";

    // Get the size of the JSON string
    size_t bufferSize = obj.measureLength() + 1;
    buffer = new char[bufferSize];

    obj.printTo(buffer, bufferSize);
}

uint256_t Tx::toUint256(const char *decimalStr) {
    std::stringstream ss;
    ss << std::hex << std::stoul(decimalStr);
    return {ss.str()};
}