#include "bip39/word_list.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

class SeedGenerator {
public:
    static BIP39::word_list passphrase;

    static void createMnemonic();

private:
    static std::vector<uint8_t> entropy;

    SeedGenerator();

    static void generateEntropy();
};

#endif //SEED_GENERATOR_H
