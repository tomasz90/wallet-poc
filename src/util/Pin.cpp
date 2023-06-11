#include "Pin.h"
#include "Wmath.cpp"

Pin::Pin() {
    clearValues();
}

void Pin::clearValues() {
    currentIndex = 0;
    rawCombination[0] = _random(0);
    rawCombination[1] = _random(-1);
    rawCombination[2] = _random(-1);
    rawCombination[3] = _random(-1);
    stateCombination[0] = DigitState::INIT;
    stateCombination[1] = DigitState::UN_INIT;
    stateCombination[2] = DigitState::UN_INIT;
    stateCombination[3] = DigitState::UN_INIT;
}

std::string Pin::getPinString() {
    std::string pinText = "       ";
    pinText[0] = getCharAt(0);
    pinText[2] = getCharAt(1);
    pinText[4] = getCharAt(2);
    pinText[6] = getCharAt(3);
    return pinText;
}

void Pin::incrementCurrentDigit() {
    int &currentNumber = rawCombination[currentIndex];
    if (currentNumber >= 9) {
        if (currentIndex == 0) {
            currentNumber = 0;
        } else {
            currentNumber = -1;
        }
    } else {
        currentNumber++;
    }
    rawCombination[currentIndex] = currentNumber;
}

void Pin::decrementCurrentDigit() {
    int &currentNumber = rawCombination[currentIndex];
    if (currentNumber == 0) {
        if (currentIndex == 0) {
            currentNumber = 9;
        } else {
            currentNumber = -1;
        }
    } else if (currentNumber == -1) {
        currentNumber = 9;
    } else {
        currentNumber--;
    }
    rawCombination[currentIndex] = currentNumber;
}

bool Pin::isArrow() {
    return rawCombination[currentIndex] == -1;
}

bool Pin::isFirstDigit() {
    return Pin::currentIndex == 0;
}

bool Pin::isLastDigit() {
    return Pin::currentIndex == 3;
}

void Pin::setOneDigit() {
    stateCombination[currentIndex] = DigitState::SET;
    if (currentIndex < 3) {
        currentIndex++;
        stateCombination[currentIndex] = DigitState::INIT;
    }
}

void Pin::unsetOneDigit() {
    if (currentIndex > 0) {
        rawCombination[currentIndex] = _random(-1);
        stateCombination[currentIndex] = DigitState::UN_INIT;
        stateCombination[currentIndex - 1] = DigitState::INIT;
        currentIndex--;
    }
}

void Pin::setPin() {
    assignArray(savedCombination, rawCombination);
}

bool Pin::confirmPin() {
    return areTheSame(savedCombination, rawCombination);
}

bool Pin::unlockPin(uint8_t pinFromFlash[4]) {
    return areTheSame(pinFromFlash, rawCombination);
}

void Pin::assignArray(uint8_t saved[4], const int raw[4]) {
    for (int i = 0; i <= 3; i++) {
        saved[i] = raw[i];
    }
}

bool Pin::areTheSame(const uint8_t saved[4], const int raw[4]) {
    for (int i = 0; i <= 3; i++) {
        if (saved[i] != raw[i]) return false;
    }
    return true;
}

int Pin::_random(int with) {
    return random(with, 9);
}

char Pin::getCharAt(int index) {
    int digit = rawCombination[index];
    switch (stateCombination[index]) {
        case DigitState::INIT:
            if (digit == -1) return '<';
            return '0' + digit;
        case DigitState::UN_INIT:
            return '*';
        case DigitState::SET:
            return '$';
    }
}

