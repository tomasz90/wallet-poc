#ifndef SEEDGENERATOR_H
#define SEEDGENERATOR_H

#include <vector>
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"
#include "bip39/bip39.h"
#include "util/Repository.h"
#include "SeedVerifier.h"
#include "SeedViewer.h"

using std::vector;
using std::array;
using std::string;
using std::find;
using namespace BIP39;

class SeedGenerator {
public:
    static void generate(SeedViewer* seedViewer, SeedVerifier* seedVerifier);
private:
    static array<int, MNEMONIC_LENGTH> generateRandomSequence();
    static vector<uint8_t> generateEntropy();
};


#endif //SEEDGENERATOR_H
