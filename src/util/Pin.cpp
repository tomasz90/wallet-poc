#include "Pin.h"
#include "Wmath.cpp"

int Pin::currentIndex = 0;
int Pin::pinCombination[4];
DigitState pinState[4];

void Pin::begin() {
    currentIndex = 0;
    pinCombination[0] = _random(0);
    pinCombination[1] = _random(-1);
    pinCombination[2] = _random(-1);
    pinCombination[3] = _random(-1);
    pinState[0] = DigitState::INIT;
    pinState[1] = DigitState::UN_INIT;
    pinState[2] = DigitState::UN_INIT;
    pinState[3] = DigitState::UN_INIT;
}

std::string Pin::getPinString() {
    std::string pinText = "       ";
    pinText[0] = getCharAt(0);
    pinText[2] = getCharAt(1);
    pinText[4] = getCharAt(2);
    pinText[6] = getCharAt(3);
    return pinText;
}

char Pin::getCharAt(int index) {
    int digit = pinCombination[index];
    switch (pinState[index]) {
        case DigitState::INIT:
            if (digit == -1) return '<';
            return '0' + digit;
        case DigitState::UN_INIT:
            return '*';
        case DigitState::SET:
            return '$';
    }
}

int Pin::isArrow() {
    return pinCombination[currentIndex] == -1;
}

void Pin::incrementCurrentNumber() {
    int &currentNumber = pinCombination[currentIndex];
    if (currentNumber >= 9) {
        if (currentIndex == 0) {
            currentNumber = 0;
        } else {
            currentNumber = -1;
        }
    } else {
        currentNumber++;
    }
    pinCombination[currentIndex] = currentNumber;
}

void Pin::decrementCurrentNumber() {
    int &currentNumber = pinCombination[currentIndex];
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
    pinCombination[currentIndex] = currentNumber;
}

void Pin::setDigit() {
    if(!Pin::isArrow()) {
        Pin::setOneDigit();
    } else {
        Pin::unsetOneDigit();
    }
}

void Pin::setOneDigit() {
    if (currentIndex == 3) {
        //currentIndex = 0;
        begin();
        // todo: remember pin combination
    } else if (currentIndex < 3) {
        pinCombination[currentIndex] = _random(-1);
        pinState[currentIndex] = DigitState::SET;
        pinState[currentIndex + 1] = DigitState::INIT;
        currentIndex++;
    }
}

void Pin::unsetOneDigit() {
    if (currentIndex > 0) {
        pinCombination[currentIndex] = _random(-1);
        pinState[currentIndex] = DigitState::UN_INIT;
        pinState[currentIndex - 1] = DigitState::INIT;
        currentIndex--;
    }
}

int Pin::_random(int with) {
    return random(with, 9);
}

