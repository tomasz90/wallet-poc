#include <array>
#include "bip39/word_list.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

#define MNEMONIC_LENGTH 12

enum class SeedVerifierMode { SET, CONFIRM };

using namespace BIP39;
using std::string;
using std::vector;
using std::array;

class SeedVerifier {
public:
    uint8_t currentIndex;
    SeedVerifierMode mode;
    word_list mnemonic;
    array<int, MNEMONIC_LENGTH> randomSequence{};

    SeedVerifier(BIP39::word_list &mnemonic, array<int, MNEMONIC_LENGTH> &randomSequence);
    void setMode(SeedVerifierMode mode);
    bool isSecond() const;
    bool isLast() const;
    void increment();
    void decrement();
    void resetIndex();
    int getCurrentRandom();
    string getCurrentWord() const;
    bool validateWord(const string &word);

};

#endif //SEED_GENERATOR_H
