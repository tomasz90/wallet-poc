#include <bootloader_random.h>
#include "SeedGenerator.h"

void SeedGenerator::generate(SeedViewer* seedViewer, SeedVerifier* seedVerifier) {
    // todo: find out if bt can be initlized to produce random, but not advertised
    bootloader_random_enable();

    // GENERATE RANDOM SEQUENCE
    array<int, MNEMONIC_LENGTH> seq = generateRandomSequence();
    seedVerifier->setRandomSequence(seq);

    // GENERATE MNEMONIC
    vector <uint8_t> entropy = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//generateEntropy();
    word_list mnemonic = create_mnemonic(entropy, language::en);
    Serial.println(mnemonic.to_string().c_str());
    seedViewer->setMnemonic(mnemonic);
    seedVerifier->setMnemonic(mnemonic);

    bootloader_random_disable();
}

array<int, MNEMONIC_LENGTH> SeedGenerator::generateRandomSequence() {
    array<int, MNEMONIC_LENGTH> seq{};
    seq.fill(-1);
    for (int &i: seq) {
        uint8_t temp = esp_random() % MNEMONIC_LENGTH;
        while (find(seq.begin(), seq.end(), temp) != seq.end()) {
            temp = esp_random() % MNEMONIC_LENGTH;
        }
        i = temp;
    }
    return seq;
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