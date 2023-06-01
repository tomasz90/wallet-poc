#include <esp_random.h>
#include "SeedGenerator.h"
#include "bip39/bip39.h"

std::vector<uint8_t> SeedGenerator::generateEntropy() {
    // Resize the vector to accommodate the desired number of bytes
    size_t numBytes = 32;
    std::vector<uint8_t> entropy;
    entropy.resize(numBytes);

    // Generate random numbers using esp_random() and store them in the vector
    for (size_t i = 0; i < numBytes; i++) {
        entropy[i] = static_cast<uint8_t>(esp_random());
    }
    return entropy;
}

BIP39::word_list SeedGenerator::createMnemonic() {
    std::vector<uint8_t> entropy = generateEntropy();
    // todo need to find out what is better
    // BIP39::generate_mnemonic(BIP39::entropy_bits_t::_256, BIP39::language::en);
    return BIP39::create_mnemonic(entropy, BIP39::language::en);
}
