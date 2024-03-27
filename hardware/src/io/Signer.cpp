#include "Signer.h"
#include "Contract.h"

void Signer::sign(EthTx* tx, string &key, char* &buffer) {
    JsonObject &obj = jb.createObject();

    Contract contract(tx->chainId);

    contract.SetPrivateKey(key.c_str());

    string encoded = contract.SignTransaction(tx->nonce, tx->gasPrice, tx->gasLimit,
                                              &tx->destinationAddress, &tx->value, &tx->data);

    string nonceStr = std::to_string(tx->nonce);
    string chainIdStr = std::to_string(tx->chainId);
    string gasPriceStr = std::to_string(tx->gasPrice);
    string gasLimitStr = std::to_string(tx->gasLimit);
    string valueStr = tx->value.str();

    obj["nonce"] = nonceStr.c_str();
    obj["chainId"] = chainIdStr.c_str();
    obj["gasPrice"] = gasPriceStr.c_str();
    obj["gasLimit"] = gasLimitStr.c_str();;
    obj["destinationAddress"] = tx->destinationAddress.c_str();
    obj["value"] = valueStr.c_str();
    obj["data"] = tx->data.c_str();
    obj["encoded"] = encoded.c_str();

    Serial.println(obj["nonce"].as<char* >());
    Serial.println(obj["chainId"].as<char* >());
    Serial.println(obj["gasPrice"].as<char* >());
    Serial.println(obj["gasLimit"].as<char* >());
    Serial.println(obj["destinationAddress"].as<char* >());
    Serial.println(obj["value"].as<char* >());
    Serial.println(obj["data"].as<char* >());
    Serial.println(obj["encoded"].as<char* >());

    // Get the size of the JSON string
    size_t bufferSize = obj.measureLength() + 1;
    buffer = new char[bufferSize];

    obj.printTo(buffer, bufferSize);
}
