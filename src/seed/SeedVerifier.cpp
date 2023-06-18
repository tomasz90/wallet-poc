#include <iostream>
#include "SeedVerifier.h"
#include "utility/trezor/sha3.h"
#include "Conversion.h"
//#include "io/Bluetooth.h"

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

bool SeedVerifier::validateHash(const string &lastTwoBytesHash) {

    string s = tempMnemonic.getWordAt(getCurrentRandom()) + "03d2fde6-1615-461d-897b-6b0220bdd335";
    auto array = reinterpret_cast<const uint8_t *>(s.c_str());

    uint8_t hash[32] = {0};
    keccak_256(array, s.length(), hash);

    uint8_t lastTwoBytes[2] = {0};
    memcpy(lastTwoBytes, hash + sizeof(hash) - sizeof lastTwoBytes, sizeof lastTwoBytes);

    string cutHashString = toHex(lastTwoBytes, sizeof lastTwoBytes).c_str();

    if (cutHashString == lastTwoBytesHash) {
        verifiedWords[getCurrentRandom()] = tempMnemonic.getWordAt(getCurrentRandom());
        return true;
    } else {
        return false;
    }
}

std::string SeedVerifier::getMnemonic() {
    return tempMnemonic.to_string();
}
