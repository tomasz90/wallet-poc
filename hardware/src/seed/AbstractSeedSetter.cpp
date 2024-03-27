#include "AbstractSeedSetter.h"
#include "const.h"

AbstractSeedSetter::AbstractSeedSetter() {
    currentIndex = 0;
}

void AbstractSeedSetter::setMnemonic(word_list &_tempMnemonic) {
    this->tempMnemonic = _tempMnemonic;
}

bool AbstractSeedSetter::isSecond() const {
    return currentIndex == 1;
}

bool AbstractSeedSetter::isLast() const {
    return currentIndex == MNEMONIC_LENGTH - 1;
}

void AbstractSeedSetter::increment() {
    if (currentIndex < MNEMONIC_LENGTH - 1) {
        currentIndex++;
    }
}

void AbstractSeedSetter::decrement() {
    if (currentIndex > 0) {
        currentIndex--;
    }
}

void AbstractSeedSetter::resetIndex() {
    currentIndex = 0;
}
