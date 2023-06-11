#include "SeedVerifier.h"

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

bool SeedVerifier::validateWord(const string &word) {
    Serial.println(("currentIndex: " + std::to_string(currentIndex)).c_str());
    if (tempMnemonic.getWordAt(getCurrentRandom()) == word) {
        verifiedWords[getCurrentRandom()] = word;
        return true;
    } else {
        return false;
    }
}
