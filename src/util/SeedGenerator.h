#include <array>
#include "bip39/word_list.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

enum class SeedGeneratorMode { SET, CONFIRM };

class SeedGenerator {
public:
    static uint8_t currentIndex;
    static std::array<int, 12> randomSequence;
    static BIP39::word_list mnemonic;
    static SeedGeneratorMode mode;

    static void createMnemonic();
    static void setMode(SeedGeneratorMode mode);
    static bool isSecond();
    static bool isLast();
    static void increment();
    static std::string getCurrentWord();
    static void decrement();
    static int getCurrentRandom();
    static bool validateWord(const std::string &word);

    static void resetIndex();

private:
    SeedGenerator() = default;
    static std::array<int, 12> generateRandomSequence();

    static std::vector<uint8_t> generateEntropy();

};

#endif //SEED_GENERATOR_H
