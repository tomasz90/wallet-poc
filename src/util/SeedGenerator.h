#include <array>
#include "bip39/word_list.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

#define MNEMONIC_LENGTH 12

enum class SeedGeneratorMode { SET, CONFIRM };

using namespace BIP39;
using std::string;
using std::vector;
using std::array;
using std::find;

class SeedGenerator {
public:
    uint8_t currentIndex;
    array<int, MNEMONIC_LENGTH> randomSequence;
    word_list mnemonic;
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
    string getCurrentWord() const;

    bool validateWord(const string &word);
private:
    void generateRandomSequence();
    vector<uint8_t> generateEntropy();

};

#endif //SEED_GENERATOR_H
