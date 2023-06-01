#include "bip39/word_list.h"

#ifndef WALLET_POC_SEED_H
#define WALLET_POC_SEED_H

#endif //WALLET_POC_SEED_H

class SeedGenerator {
public:
    static BIP39::word_list passphrase;

    static void createMnemonic();

private:
    static std::vector<uint8_t> entropy;

    SeedGenerator();

    static void generateEntropy();
};
