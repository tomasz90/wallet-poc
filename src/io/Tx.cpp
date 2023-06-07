#include <Arduino.h>
#include "Tx.h"

Tx::Tx() {}

Tx::Tx(std::string &receiverValue) {
    JsonObject &obj = jb.parseObject(receiverValue.c_str());
    if (!obj.success()) {
        Serial.println("parseObject() failed");
        return;
    }
    nonce = obj["nonce"];
    gasPrice = obj["gasPrice"].as<char *>();
    gasLimit = obj["gasLimit"];
    destinationAddress = obj["destinationAddress"].as<char *>();
    value = obj["value"].as<char *>();
    data = obj["data"].as<char *>();
}

void Tx::serialize(char *&buffer) {
    JsonObject& obj = jb.createObject();

    obj["nonce"] = nonce;
    obj["gasPrice"] = gasPrice.c_str();
    obj["gasLimit"] = gasLimit;
    obj["destinationAddress"] = destinationAddress.c_str();
    obj["value"] = value.c_str();
    obj["data"] = data.c_str();

    // Get the size of the JSON string
    size_t bufferSize = obj.measureLength() + 1;
    buffer = new char[bufferSize];

    obj.printTo(buffer, bufferSize);
}