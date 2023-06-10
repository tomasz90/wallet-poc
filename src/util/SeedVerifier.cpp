#include "SeedVerifier.h"

SeedVerifier::SeedVerifier(DataHolder *dataHolder) {
    currentIndex = 0;
    this->mnemonic = dataHolder->mnemonic;
    this->randomSequence = dataHolder->randomSequence;
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
    return mnemonic.getWordAt(randomSequence[currentIndex]);
}

bool SeedVerifier::validateWord(const string &word) {
    return getCurrentRandomWord() == word;
}
