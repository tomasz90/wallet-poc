#include <array>
#include "bip39/word_list.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

class SeedGenerator {
public:
    static uint8_t currentIndex;
    static std::array<int, 24> randomSequence;
    static BIP39::word_list mnemonic;

    static void createMnemonic();
    static void increment();
    static std::string getCurrentWord();
    static void decrement();
    static int getCurrentRandom();
    static bool validateWord(const std::string &word);
private:
    SeedGenerator() = default;
    static std::array<int, 24> generateRandomSequence();
    static std::vector<uint8_t> generateEntropy();
};

#endif //SEED_GENERATOR_H
