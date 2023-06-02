#include <esp_random.h>
#include <HardwareSerial.h>
#include "SeedGenerator.h"
#include "bip39/bip39.h"
#include "Util.h"

BIP39::word_list SeedGenerator::mnemonic;
uint8_t SeedGenerator::currentIndex = 0;
uint8_t SeedGenerator::randomSequence[MNEMONIC_LENGTH];
SeedGeneratorMode SeedGenerator::mode;

void SeedGenerator::createMnemonic() {
    std::vector<uint8_t> entropy = generateEntropy();
    mnemonic = BIP39::create_mnemonic(entropy, BIP39::language::en);
    Serial.println(mnemonic.to_string().c_str());
    generateRandomSequence();
}

void SeedGenerator::setMode(SeedGeneratorMode _mode) {
    mode = _mode;
}

bool SeedGenerator::isSecond() {
    return currentIndex == 1;
}

bool SeedGenerator::isLast() {
    return currentIndex == MNEMONIC_LENGTH - 1;
}

void SeedGenerator::increment() {
    if(currentIndex < MNEMONIC_LENGTH - 1) {
        currentIndex++;
    } else {
        throwException("SeedGenerator: Index out of bounds");
    }
}

void SeedGenerator::decrement() {
    if(currentIndex > 0) {
        currentIndex--;
    } else {
        throwException("SeedGenerator: Index out of bounds");
    }
}

void SeedGenerator::resetIndex() {
    currentIndex = 0;
}

int SeedGenerator::getCurrentRandom() {
    return randomSequence[currentIndex];
}

std::string SeedGenerator::getCurrentWord() {
    return mnemonic.getWordAt(currentIndex);
}

bool SeedGenerator::validateWord(const std::string &word) {
    return mnemonic.getWordAt(randomSequence[currentIndex]) == word;
}

void SeedGenerator::generateRandomSequence() {
    for (unsigned char &i : randomSequence) {
        i = esp_random() % MNEMONIC_LENGTH;
    }
}

std::vector<uint8_t> SeedGenerator::generateEntropy() {
    // Resize the vector to accommodate the desired number of bytes
    size_t numBytes = 16;
    std::vector<uint8_t> entropy(numBytes);

    // Generate random numbers using esp_random() and store them in the vector
    for (size_t i = 0; i < numBytes; i++) {
        entropy[i] = static_cast<uint8_t>(esp_random());
    }
    return entropy;
}
