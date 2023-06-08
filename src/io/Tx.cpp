#include <Arduino.h>
#include <sstream>
#include "Tx.h"
#include "Contract.h"
#include "/Users/tomasz/CLionProjects/wallet-poc/.pio/libdeps/esp32dev/Web3E/src/Util.h"

#define SIGNATURE_LENGTH 64

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
    value = uint256_t(obj["value"].as<char *>());
    data = obj["data"].as<char *>();

}

void Tx::sign(char *&buffer) {
    JsonObject &obj = jb.createObject();

    uint8_t signature[SIGNATURE_LENGTH];
    memset(signature, 0, SIGNATURE_LENGTH);
    int recid[1] = {0};
    auto web3 = new Web3(GOERLI_ID);
    Contract contract(web3, "");
    contract.SetPrivateKey("0x4646464646464646464646464646464646464646464646464646464646464646");

    auto *chainId = new string("1");
    auto *zero = new string("0");
    contract.GenerateSignature(signature, recid, nonce, gasPrice, gasLimit,
                      &destinationAddress, &value, &data, chainId, zero);

    vector<uint8_t> param = contract.RlpEncodeForRawTransaction(nonce, gasPrice, gasLimit,
                                                       &destinationAddress, &value, &data,
                                                       signature, recid[0], chainId, zero);

    string encoded = Util::VectorToString(&param);

    string nonceStr = std::to_string(nonce);
    string gasPriceStr = std::to_string(gasPrice);
    string gasLimitStr = std::to_string(gasLimit);
    string valueStr = value.str();

    obj["nonce"] = nonceStr.c_str();
    obj["gasPrice"] = gasPriceStr.c_str();
    obj["gasLimit"] = gasLimitStr.c_str();;
    obj["destinationAddress"] = destinationAddress.c_str();
    obj["value"] = valueStr.c_str();
    obj["data"] = data.c_str();
    obj["encoded"] = encoded.c_str();

    Serial.println(obj["nonce"].as<char *>());
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

//uint256_t Tx::toUint256(const char *decimalStr) {
//    std::stringstream ss;
//    ss << std::hex << std::stoull(decimalStr);
//    return {ss.str()};
//}

//0xF86F098504A817C800825208943535353535353535353535353535353535353535880DE0B6B3A764000080        25A028EF61340BD939BC2195FE537567866003E1A15D3C71FF63E1590620AA636276A067CBE9D8997F761AECB703304B3800CCF555C9F3DC64214B297FB1966A3B6D83
//0xF86F098504A817C800825208943535353535353535353535353535353535353535880DE0B6B3A764000080   8080 25A028EF61340BD939BC2195FE537567866003E1A15D3C71FF63E1590620AA636276A067CBE9D8997F761AECB703304B3800CCF555C9F3DC64214B297FB1966A3B6D83
//0xF86F098504A817C800825208943535353535353535353535353535353535353535880DE0B6B3A7640000   018080 25A028EF61340BD939BC2195FE537567866003E1A15D3C71FF63E1590620AA636276A067CBE9D8997F761AECB703304B3800CCF555C9F3DC64214B297FB1966A3B6D83
//0xF86F098504A817C8008252089435353535353535353535353535353535353535358 0                  018080 25A028EF61340BD939BC2195FE537567866003E1A15D3C71FF63E1590620AA636276A067CBE9D8997F761AECB703304B3800CCF555C9F3DC64214B297FB1966A3B6D83
//0xF86F098504A817C800      943535353535353535353535353535353535353535880DE0B6B3A764000080 018080 25A028EF61340BD939BC2195FE537567866003E1A15D3C71FF63E1590620AA636276A067CBE9D8997F761AECB703304B3800CCF555C9F3DC64214B297FB1966A3B6D83
//0xF86F098504A817C800825208943535353535353535353535353535353535353535880DE0B6B3A764000080 018080 25A028EF61340BD939BC2195FE537567866003E1A15D3C71FF63E1590620AA636276A067CBE9D8997F761AECB703304B3800CCF555C9F3DC64214B297FB1966A3B6D83
//0XF86C098504A817C800825208943535353535353535353535353535353535353535880DE0B6B3A764000080        25A028EF61340BD939BC2195FE537567866003E1A15D3C71FF63E1590620AA636276A067CBE9D8997F761AECB703304B3800CCF555C9F3DC64214B297FB1966A3B6D83
//0xF86C098504A817C800825208943535353535353535353535353535353535353535880DE0B6B3A764000080        25A028EF61340BD939BC2195FE537567866003E1A15D3C71FF63E1590620AA636276A067CBE9D8997F761AECB703304B3800CCF555C9F3DC64214B297FB1966A3B6D83