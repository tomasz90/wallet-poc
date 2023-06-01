#include "bip39/word_list.h"

#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

class SeedGenerator {
public:
    static BIP39::word_list createMnemonic();

private:
    SeedGenerator() = default;

    static std::vector<uint8_t> generateEntropy();
};

#endif //SEED_GENERATOR_H
