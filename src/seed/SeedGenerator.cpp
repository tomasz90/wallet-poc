#include <bootloader_random.h>
#include "SeedGenerator.h"

void SeedGenerator::generate(SeedViewer *seedViewer, SeedVerifier *seedVerifier) {
    // GENERATE RANDOMNESS
//    bootloader_random_enable();
//    bootloader_random_disable();

    // GENERATE RANDOM SEQUENCE
    array<int, MNEMONIC_LENGTH> seq{};
    generateRandomSequence(seq);

    // GENERATE MNEMONIC
    vector<uint8_t> entropy = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//generateEntropy();
    word_list mnemonic = create_mnemonic(entropy, language::en);

    seedViewer->setMnemonic(mnemonic);
    seedVerifier->setMnemonic(mnemonic);
    seedVerifier->setRandomSequence(seq);
}

void SeedGenerator::generateRandomSequence(array<int, MNEMONIC_LENGTH> seq) {
    seq.fill(-1);
    for (int &i: seq) {
        uint8_t temp = esp_random() % MNEMONIC_LENGTH;
        while (find(seq.begin(), seq.end(), temp) != seq.end()) {
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