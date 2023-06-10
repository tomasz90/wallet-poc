#include <array>
#include "bip39/word_list.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

#define MNEMONIC_LENGTH 12

enum class SeedVerifierMode { SET, CONFIRM };

using namespace BIP39;
using std::string;
using std::vector;
using std::array;
using std::find;

class SeedVerifier {
public:
    uint8_t currentIndex;
    array<int, MNEMONIC_LENGTH> randomSequence;
    word_list mnemonic;
    SeedVerifierMode mode;
    EthereumHDPrivateKey *account;

    SeedVerifier();
    void setMode(SeedVerifierMode mode);
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