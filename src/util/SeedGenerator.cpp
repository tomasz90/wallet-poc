#include <esp_random.h>
#include <HardwareSerial.h>
#include <bootloader_random.h>
#include <algorithm>
#include "SeedGenerator.h"
#include "bip39/bip39.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"

SeedGenerator::SeedGenerator() {
    currentIndex = 0;
    // GENERATE RANDOMNESS
    bootloader_random_enable();
    vector<uint8_t> entropy = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};//generateEntropy();
    generateRandomSequence();
    bootloader_random_disable();

    mnemonic = create_mnemonic(entropy, language::en);
    Serial.println(mnemonic.to_string().c_str());
    EthereumHDPrivateKey hd(String(mnemonic.to_string().c_str()));
    account = hd.derive("m/44'/60'/0'/0/0");
}

void SeedGenerator::setMode(SeedGeneratorMode _mode) {
    mode = _mode;
}

bool SeedGenerator::isSecond() const {
    return currentIndex == 1;
}

bool SeedGenerator::isLast() const {
    return currentIndex == MNEMONIC_LENGTH - 1;
}

void SeedGenerator::increment() {
    if (currentIndex < MNEMONIC_LENGTH - 1) {
        currentIndex++;
    }
}

void SeedGenerator::decrement() {
    if (currentIndex > 0) {
        currentIndex--;
    }
}

void SeedGenerator::resetIndex() {
    currentIndex = 0;
}

int SeedGenerator::getCurrentRandom() {
    return randomSequence[currentIndex];
}

string SeedGenerator::getCurrentWord() const {
    return mnemonic.getWordAt(currentIndex);
}

bool SeedGenerator::validateWord(const string &word) {
    return mnemonic.getWordAt(randomSequence[currentIndex]) == word;
}

void SeedGenerator::generateRandomSequence() {
    string s;
    randomSequence.fill(-1);
    for (int &i: randomSequence) {
        uint8_t temp = esp_random() % MNEMONIC_LENGTH;
        while (find(randomSequence.begin(), randomSequence.end(), temp) != randomSequence.end()) {
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
