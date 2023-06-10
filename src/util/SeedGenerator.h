#ifndef SEEDGENERATOR_H
#define SEEDGENERATOR_H

#include <vector>
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"
#include "bip39/bip39.h"
#include "DataHolder.h"

using std::vector;
using std::string;
using std::find;
using namespace BIP39;

class SeedGenerator {
public:
    SeedGenerator(DataHolder *dataHolder);
private:
    void generateRandomSequence(DataHolder *dataHolder);
    vector<uint8_t> generateEntropy();
};


#endif //SEEDGENERATOR_H
