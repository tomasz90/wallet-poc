#include <esp_random.h>
#include <random>
#include <algorithm>
#include <HardwareSerial.h>
#include "SeedGenerator.h"
#include "bip39/bip39.h"

BIP39::word_list SeedGenerator::mnemonic;
uint8_t SeedGenerator::currentIndex = 0;
std::array<int, 12> SeedGenerator::randomSequence;

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

void SeedGenerator::createMnemonic() {
    std::vector<uint8_t> entropy = generateEntropy();
    mnemonic = BIP39::create_mnemonic(entropy, BIP39::language::en);
    randomSequence = generateRandomSequence();
}

std::string SeedGenerator::getCurrentWord() {
    return mnemonic.getWordAt(currentIndex);
}

void SeedGenerator::increment() {
    if(currentIndex < 11) {
        currentIndex++;
    } else {
        currentIndex = 0;
    }
}

void SeedGenerator::decrement() {
    if(currentIndex > 0) {
        currentIndex--;
    }
}

std::array<int, 12> SeedGenerator::generateRandomSequence() {
    std::array<int, 12> numbers{};

    for (int i = 0; i < 12; ++i) {
        numbers[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);
    return numbers;
}

int SeedGenerator::getCurrentRandom() {
    return randomSequence[currentIndex];
}

bool SeedGenerator::validateWord(const std::string &word) {
    Serial.println(mnemonic.getWordAt(currentIndex).c_str());
    Serial.println(currentIndex);
    Serial.println(word.c_str());
    return mnemonic.getWordAt(currentIndex) == word;
}

bool SeedGenerator::isSecond() {
    return currentIndex == 1;
}

bool SeedGenerator::isLast() {
    return currentIndex == 11;
}
