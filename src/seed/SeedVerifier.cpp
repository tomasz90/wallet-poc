#include <iostream>
#include "SeedVerifier.h"
#include "utility/trezor/sha3.h"
#include "Conversion.h"
#include "bip39/bip39.h"

SeedVerifier::SeedVerifier() : AbstractSeedSetter() {
    this->verifiedWords.fill("");
}

void SeedVerifier::setRandomSequence(array<int, MNEMONIC_LENGTH> seq) {
    this->randomSequence = seq;
}

int SeedVerifier::getCurrentRandom() {
    return randomSequence[currentIndex];
}

string SeedVerifier::getCurrentRandomWord() {
    return verifiedWords[getCurrentRandom()];
}

bool SeedVerifier::isCurrentWordValid() {
    return !getCurrentRandomWord().empty();
}

bool SeedVerifier::validateHash(const string &lastBytesHash) {

    string s = tempMnemonic.getWordAt(getCurrentRandom()) + RECEIVER_UUID;

    if (computeHash(s) == lastBytesHash) {
        verifiedWords[getCurrentRandom()] = tempMnemonic.getWordAt(getCurrentRandom());
        return true;
    } else {
        return false;
    }
}

bool SeedVerifier::findWord(const string &lastBytesHash) {
    const auto lexicon = get_string_table(language::en);

    for (int i = 0; i < 2048; i++) {
        string s = lexicon[i];
        s.append(RECEIVER_UUID);

        if (computeHash(s) == lastBytesHash) {
            return lexicon[i];
        }
    }
    return "";
}

string SeedVerifier::computeHash(const string &s) {
    auto array = reinterpret_cast<const uint8_t *>(s.c_str());

    uint8_t hash[32] = {0};
    keccak_256(array, s.length(), hash);

    uint8_t lastBytes[8] = {0};
    memcpy(lastBytes, hash + sizeof(hash) - sizeof lastBytes, sizeof lastBytes);

    return toHex(lastBytes, sizeof lastBytes).c_str();
}

std::string SeedVerifier::getMnemonic() {
    return tempMnemonic.to_string();
}
