#ifndef SEED_VERIFIER_H
#define SEED_VERIFIER_H

#include "AbstractSeedSetter.h"

class SeedVerifier : public AbstractSeedSetter {
public:
    explicit SeedVerifier(DataHolder *dataHolder);
    int getCurrentRandom();
    string getCurrentRandomWord();
    bool validateWord(const string &word);
    bool isCurrentWordValid();

private:
    array<int, MNEMONIC_LENGTH> randomSequence{};
    array<string, MNEMONIC_LENGTH> verifiedWords;
};

#endif //SEED_VERIFIER_H
