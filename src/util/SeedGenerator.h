#include "bip39/word_list.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

class SeedGenerator {
public:
    static uint8_t currentWordIndex;
    static BIP39::word_list mnemonic;

    static void createMnemonic();
    static void increment();
    static std::string getCurrentWord();

    static void decrement();

private:
    SeedGenerator() = default;

    static std::vector<uint8_t> generateEntropy();
};

#endif //SEED_GENERATOR_H
