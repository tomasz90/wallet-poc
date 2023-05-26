#include <esp_random.h>
#include "seed.h"
#include "bip39/bip39.h"

std::vector<uint8_t> Seed::entropy;

BIP39::word_list Seed::passphrase;

void Seed::generateEntropy() {
    // Resize the vector to accommodate the desired number of bytes
    size_t numBytes = 256;
    entropy.resize(numBytes);

    // Generate random numbers using esp_random() and store them in the vector
    for (size_t i = 0; i < 256; ++i) {
        entropy[i] = static_cast<uint8_t>(esp_random());
    }
}

void Seed::createMnemonic() {
    Seed::generateEntropy();
    passphrase = BIP39::create_mnemonic(entropy, BIP39::language::en);
}
