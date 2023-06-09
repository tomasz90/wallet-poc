#include <array>
#include "bip39/word_list.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

#define MNEMONIC_LENGTH 12

enum class SeedGeneratorMode { SET, CONFIRM };

class SeedGenerator {
public:
    static uint8_t currentIndex;
    static std::array<int, MNEMONIC_LENGTH> randomSequence;
    static BIP39::word_list mnemonic;
    static SeedGeneratorMode mode;
    static EthereumHDPrivateKey *account;

    static void createMnemonic();
    static void setMode(SeedGeneratorMode mode);
    static bool isSecond();
    static bool isLast();
    static void increment();
    static void decrement();
    static void resetIndex();
    static int getCurrentRandom();
    static std::string getCurrentWord();
    static bool validateWord(const std::string &word);

private:
    SeedGenerator() = default;
    static void generateRandomSequence();
    static std::vector<uint8_t> generateEntropy();

};

#endif //SEED_GENERATOR_H
