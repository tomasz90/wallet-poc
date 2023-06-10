#include <array>
#include "bip39/word_list.h"
#include "SeedGenerator.h"

#ifndef SEED_VERIFIER_H
#define SEED_VERIFIER_H

enum class SeedVerifierMode { SET, CONFIRM };

using namespace BIP39;
using std::vector;
using std::array;
using std::string;

class SeedVerifier {
public:
    uint8_t currentIndex;
    SeedVerifierMode mode;

    SeedVerifier(DataHolder *dataHolder);
    void setMode(SeedVerifierMode mode);
    bool isSecond() const;
    bool isLast() const;
    void increment();
    void decrement();
    void resetIndex();
    int getCurrentRandom();
    string getCurrentWord() const;
    string getCurrentRandomWord();
    bool validateWord(const string &word);

    bool isCurrentWordValid();

private:
    word_list mnemonic;
    array<int, MNEMONIC_LENGTH> randomSequence;
    array<string, MNEMONIC_LENGTH> verifiedWords;

};

#endif //SEED_VERIFIER_H
