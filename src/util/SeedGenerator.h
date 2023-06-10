#ifndef SEEDGENERATOR_H
#define SEEDGENERATOR_H

#include <vector>
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"
#include "bip39/bip39.h"
#include "DataHolder.h"

using std::vector;
using std::array;
using std::string;
using std::find;
using namespace BIP39;

class SeedGenerator {
public:
    static void generate(DataHolder *dataHolder);
private:
    static void generateRandomSequence(DataHolder *dataHolder);
    static vector<uint8_t> generateEntropy();
};


#endif //SEEDGENERATOR_H
