#include "SeedVerifier.h"

SeedVerifier::SeedVerifier(DataHolder *dataHolder) : AbstractSeedSetter(dataHolder) {
    this->randomSequence = dataHolder->randomSequence;
    this->verifiedWords.fill("");
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
    if (mnemonic.getWordAt(getCurrentRandom()) == word) {
        verifiedWords[getCurrentRandom()] = word;
        return true;
    } else {
        return false;
    }
}
