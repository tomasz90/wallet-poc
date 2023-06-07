#include <Arduino.h>
#include <sstream>
#include "Tx.h"
#include "Contract.h"
#include "/Users/tomasz/CLionProjects/wallet-poc/.pio/libdeps/esp32dev/Web3E/src/Util.h"

Tx::Tx() {}

Tx::Tx(std::string &receiverValue) {
    JsonObject &obj = jb.parseObject(receiverValue.c_str());
    if (!obj.success()) {
        Serial.println("parseObject() failed");
        return;
    }
    nonce = obj["nonce"].as<uint32_t>();
    gasPrice = std::stoull(obj["gasPrice"].as<char *>());
    gasLimit = obj["gasLimit"].as<uint32_t>();
    destinationAddress = obj["destinationAddress"].as<char *>();
    value = toUint256(obj["value"].as<char *>());
    data = obj["data"].as<char *>();

}

void Tx::sign(char *&buffer) {
    JsonObject &obj = jb.createObject();

    uint8_t signature[ETHERS_SIGNATURE_LENGTH];
    memset(signature, 0, ETHERS_SIGNATURE_LENGTH);
    int recid[1] = {0};
    auto web3 = new Web3(GOERLI_ID);
    Contract contract(web3, "");
    contract.SetPrivateKey("0x6d304a7dfcdbc740c38f4102e47135d73ef1347f1316bfe608e73f8151062821");

    contract.GenerateSignature(signature, recid, nonce, gasPrice, gasLimit,
                      &destinationAddress, &value, &data);

    string nonceStr = std::to_string(nonce);
    string gasPriceStr = std::to_string(gasPrice);
    string gasLimitStr = std::to_string(gasLimit);
    string valueStr = value.str();
    string signatureStr = Util::ConvertBytesToHex(signature, ETHERS_SIGNATURE_LENGTH);

    obj["nonce"] = nonceStr.c_str();
    obj["gasPrice"] = gasPriceStr.c_str();
    obj["gasLimit"] = gasLimitStr.c_str();;
    obj["destinationAddress"] = destinationAddress.c_str();
    obj["value"] = valueStr.c_str();
    obj["data"] = data.c_str();
    obj["signature"] = signatureStr.c_str();

    Serial.println(obj["nonce"].as<char *>());
    Serial.println(obj["gasPrice"].as<char *>());
    Serial.println(obj["gasLimit"].as<char *>());
    Serial.println(obj["destinationAddress"].as<char *>());
    Serial.println(obj["value"].as<char *>());
    Serial.println(obj["data"].as<char *>());
    Serial.println(obj["signature"].as<char *>());

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