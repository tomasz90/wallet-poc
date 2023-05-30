#include <HardwareSerial.h>
#include "Pin.h"
#include "Wmath.cpp"
#include "Util.h"

int Pin::currentIndex = 0;
int Pin::rawCombination[4];
int Pin::savedCombination[4];
DigitState pinState[4];

void Pin::begin() {
    currentIndex = 0;
    rawCombination[0] = _random(0);
    rawCombination[1] = _random(-1);
    rawCombination[2] = _random(-1);
    rawCombination[3] = _random(-1);
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
    int digit = rawCombination[index];
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

bool Pin::isArrow() {
    return rawCombination[currentIndex] == -1;
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

void Pin::setDigit() {
    if (!Pin::isArrow()) {
        Pin::setOneDigit();
    } else {
        Pin::unsetOneDigit();
    }
}

void Pin::setOneDigit() {
    if (currentIndex == 3) {
        begin();
    } else if (currentIndex < 3) {
        pinState[currentIndex] = DigitState::SET;
        pinState[currentIndex + 1] = DigitState::INIT;
        currentIndex++;
    }
}

void Pin::unsetOneDigit() {
    if (currentIndex > 0) {
        rawCombination[currentIndex] = _random(-1);
        pinState[currentIndex] = DigitState::UN_INIT;
        pinState[currentIndex - 1] = DigitState::INIT;
        currentIndex--;
    }
}

int Pin::_random(int with) {
    return random(with, 9);
}

void Pin::savePin() {
    Serial.println("Saving pin");
    for (int i = 0; i < 4; i++) {
        if(rawCombination[i] < 0) throwException("Invalid digit at index: " + String(i) + " value: " + rawCombination[i]);
        savedCombination[i] = rawCombination[i];
        Serial.print(savedCombination[i]);
    }
}

