#ifndef SEED_VERIFIER_H
#define SEED_VERIFIER_H

#include "AbstractSeedSetter.h"
#include "const.h"

class SeedVerifier : public AbstractSeedSetter {
public:
    array<int, MNEMONIC_LENGTH> randomSequence{};

    explicit SeedVerifier();
    void setRandomSequence(array<int, MNEMONIC_LENGTH> seq);
    int getCurrentRandom();
    string getCurrentRandomWord();
    bool validateWord(const string &word);
    bool isCurrentWordValid();

private:
    array<string, MNEMONIC_LENGTH> verifiedWords;
};

#endif //SEED_VERIFIER_H
