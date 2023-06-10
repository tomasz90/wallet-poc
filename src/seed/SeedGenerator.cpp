#include <bootloader_random.h>
#include "SeedGenerator.h"

#define DEFAULT_PATH "m/44'/60'/0'/0/0"

void SeedGenerator::generate(DataHolder *dataHolder) {
    // GENERATE RANDOMNESS
    bootloader_random_enable();
    vector<uint8_t> entropy = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//generateEntropy();
    generateRandomSequence(dataHolder);
    bootloader_random_disable();

    dataHolder->mnemonic = create_mnemonic(entropy, language::en);
    EthereumHDPrivateKey hd(dataHolder->mnemonic.to_string());
    dataHolder->account = hd.derive(DEFAULT_PATH);
    Serial.println(dataHolder->mnemonic.to_string().c_str());
}

void SeedGenerator::generateRandomSequence(DataHolder *dataHolder) {
    array<int, MNEMONIC_LENGTH> seq{};
    seq.fill(-1);
    for (int &i: seq) {
        uint8_t temp = esp_random() % MNEMONIC_LENGTH;
        while (find(seq.begin(), seq.end(), temp) != seq.end()) {
            temp = esp_random() % MNEMONIC_LENGTH;
        }
        i = temp;
    }
    dataHolder->randomSequence = seq;
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