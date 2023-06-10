#include "SeedVerifier.h"

SeedVerifier::SeedVerifier(DataHolder *dataHolder) {
    currentIndex = 0;
    this->mnemonic = dataHolder->mnemonic;
    this->randomSequence = dataHolder->randomSequence;
    this->verifiedWords.fill("");
}

void SeedVerifier::setMode(SeedVerifierMode _mode) {
    mode = _mode;
}

bool SeedVerifier::isSecond() const {
    return currentIndex == 1;
}

bool SeedVerifier::isLast() const {
    return currentIndex == MNEMONIC_LENGTH - 1;
}

void SeedVerifier::increment() {
    if (currentIndex < MNEMONIC_LENGTH - 1) {
        currentIndex++;
    }
}

void SeedVerifier::decrement() {
    if (currentIndex > 0) {
        currentIndex--;
    }
}

void SeedVerifier::resetIndex() {
    currentIndex = 0;
}

int SeedVerifier::getCurrentRandom() {
    return randomSequence[currentIndex];
}

string SeedVerifier::getCurrentWord() const {
    return mnemonic.getWordAt(currentIndex);
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
