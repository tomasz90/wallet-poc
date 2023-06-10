#ifndef SEEDGENERATOR_H
#define SEEDGENERATOR_H

#include <vector>
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"
#include "bip39/bip39.h"
#include "SeedVerifier.h"

using std::vector;
using std::string;
using std::find;
using namespace BIP39;

class SeedGenerator {
public:
    word_list mnemonic;
    array<int, MNEMONIC_LENGTH> randomSequence;
    EthereumHDPrivateKey *account;

    SeedGenerator();
private:
    void generateRandomSequence();
    vector<uint8_t> generateEntropy();
};


#endif //SEEDGENERATOR_H
