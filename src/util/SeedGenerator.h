#include <array>
#include "bip39/word_list.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

#define MNEMONIC_LENGTH 12

enum class SeedGeneratorMode { SET, CONFIRM };

class SeedGenerator {
public:
    uint8_t currentIndex;
    std::array<int, MNEMONIC_LENGTH> randomSequence;
    BIP39::word_list mnemonic;
    SeedGeneratorMode mode;
    EthereumHDPrivateKey *account;

    SeedGenerator();
    void setMode(SeedGeneratorMode mode);
    bool isSecond() const;
    bool isLast() const;
    void increment();
    void decrement();
    void resetIndex();
    int getCurrentRandom();
    std::string getCurrentWord() const;

    bool validateWord(const std::string &word);
private:
    void generateRandomSequence();
    std::vector<uint8_t> generateEntropy();

};

#endif //SEED_GENERATOR_H
