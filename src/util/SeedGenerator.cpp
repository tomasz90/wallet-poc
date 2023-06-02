#include <esp_random.h>
#include <HardwareSerial.h>
#include <bootloader_random.h>
#include <algorithm>
#include <sstream>
#include <ios>
#include <iomanip>
#include "SeedGenerator.h"
#include "bip39/bip39.h"
#include "bip39.h"

BIP39::word_list SeedGenerator::mnemonic;
uint8_t SeedGenerator::currentIndex = 0;
std::array<int, MNEMONIC_LENGTH> SeedGenerator::randomSequence;
SeedGeneratorMode SeedGenerator::mode;

void SeedGenerator::createMnemonic() {
    bootloader_random_enable();
    std::vector<uint8_t> entropy = generateEntropy();
    mnemonic = BIP39::create_mnemonic(entropy, BIP39::language::en);
    Serial.println(mnemonic.to_string().c_str());

    uint8_t seed[512 / 8];

    mnemonic_to_seed(mnemonic.to_string().c_str(), "", seed, 0);

    std::stringstream ss;
    for (int i = 0; i < sizeof(seed); i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(seed[i]);
    }
    std::string hexString = ss.str();

    Serial.println("SEED:  ");
    Serial.println(hexString.c_str());
    generateRandomSequence();
    bootloader_random_disable();
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

std::string SeedGenerator::getCurrentWord() {
    return mnemonic.getWordAt(currentIndex);
}

bool SeedGenerator::validateWord(const std::string &word) {
    return mnemonic.getWordAt(randomSequence[currentIndex]) == word;
}

void SeedGenerator::generateRandomSequence() {
    std::string s;
    randomSequence.fill(-1);
    for (int &i: randomSequence) {
        uint8_t temp = esp_random() % MNEMONIC_LENGTH;
        while (std::find(randomSequence.begin(), randomSequence.end(), temp) != randomSequence.end()) {
            temp = esp_random() % MNEMONIC_LENGTH;
        }
        i = temp;
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
