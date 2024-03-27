#ifndef SEED_VERIFIER_H
#define SEED_VERIFIER_H

#include "AbstractSeedSetter.h"
#include "const.h"

class SeedVerifier : public AbstractSeedSetter {
public:
    explicit SeedVerifier();
    void setRandomSequence(array<int, MNEMONIC_LENGTH> seq);
    int getCurrentRandom();
    string getCurrentRandomWord();
    bool validateHash(const string &lastBytesHash);
    bool isCurrentWordValid();
    string getMnemonic();

    bool findWord(const string &lastBytesHash);

private:
    array<int, MNEMONIC_LENGTH> randomSequence{};
    array<string, MNEMONIC_LENGTH> verifiedWords;

    string computeHash(const string &s);

};

#endif //SEED_VERIFIER_H
