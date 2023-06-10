#include <bootloader_random.h>
#include "SeedGenerator.h"

SeedGenerator::SeedGenerator(DataHolder *dataHolder) {
    // GENERATE RANDOMNESS
    bootloader_random_enable();
    vector<uint8_t> entropy = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};//generateEntropy();
    generateRandomSequence(dataHolder);
    bootloader_random_disable();

    dataHolder->mnemonic = create_mnemonic(entropy, language::en);
    EthereumHDPrivateKey hd(dataHolder->mnemonic.to_string());
    dataHolder->account = hd.derive("m/44'/60'/0'/0/0");
    Serial.println(dataHolder->mnemonic.to_string().c_str());
}

void SeedGenerator::generateRandomSequence(DataHolder *dataHolder) {
    string s;
    std::array<int, MNEMONIC_LENGTH> randomSequence = dataHolder->randomSequence;
    randomSequence.fill(-1);
    for (int &i: randomSequence) {
        uint8_t temp = esp_random() % MNEMONIC_LENGTH;
        while (std::find(randomSequence.begin(), randomSequence.end(), temp) != randomSequence.end()) {
            temp = esp_random() % MNEMONIC_LENGTH;
        }
        i = temp;
    }
}

vector<uint8_t> SeedGenerator::generateEntropy() {

    // Resize the vector to accommodate the desired number of bytes
    size_t numBytes = 16;
    vector<uint8_t> entropy(numBytes);

    // Generate random numbers using esp_random() and store them in the vector
    for (size_t i = 0; i < numBytes; i++) {
        entropy[i] = static_cast<uint8_t>(esp_random());
    }
    return entropy;
}