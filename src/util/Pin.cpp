#include <HardwareSerial.h>
#include "Pin.h"
#include "Wmath.cpp"
#include "Util.h"
#include "Nav.h"

PinMode Pin::mode;
int Pin::currentIndex = 0;
int Pin::rawCombination[4];
int Pin::savedCombination[4];
DigitState pinState[4];

void Pin::clearValues() {
    currentIndex = 0;
    rawCombination[0] = _random(-1);
    rawCombination[1] = _random(-1);
    rawCombination[2] = _random(-1);
    rawCombination[3] = _random(-1);
    pinState[0] = DigitState::INIT;
    pinState[1] = DigitState::UN_INIT;
    pinState[2] = DigitState::UN_INIT;
    pinState[3] = DigitState::UN_INIT;
}

void Pin::setMode(PinMode _mode) {
    clearValues();
    mode = _mode;
    switch (mode) {
        case PinMode::SET:
            rawCombination[0] = _random(-1);
            break;
        case PinMode::CONFIRM:
            rawCombination[0] = _random(0);
            break;
    }
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

void Pin::setOrUnsetDigit() {
    if (!Pin::isArrow()) {
        Pin::setOneDigit();
    } else {
        Pin::unsetOneDigit();
    }
}

bool Pin::savePin() {
    //todo: uncomment exceptions
    //if (currentIndex != 3) throwException("Invalid current index: " + String(currentIndex));
    for (int i = 0; i < 4; i++) {
        //if (rawCombination[i] < 0) throwException("Invalid digit at index: " + String(i) + " value: " + rawCombination[i]);
        switch (mode) {
            case PinMode::SET:
                savedCombination[i] = rawCombination[i];
                break;
            case PinMode::CONFIRM:
                if (savedCombination[i] != rawCombination[i]) { return false; }
                break;
        }
    }
    clearValues();
    return true;
}

bool Pin::ifLastDigitIsDigit() {
    return !Pin::isArrow() && Pin::currentIndex == 3;
}

bool Pin::ifFirstDigitIsArrow() {
    return Pin::isArrow() && Pin::currentIndex == 0;
}

int Pin::_random(int with) {
    return random(with, 9);
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

void Pin::setOneDigit() {
    //if (currentIndex > 3) throwException("Setting at index more than 3");
    Serial.println("Setting at index: " + String(currentIndex) + " value: " + String(rawCombination[currentIndex]));
    pinState[currentIndex] = DigitState::SET;
    if (currentIndex < 3) {
        currentIndex++;
        pinState[currentIndex] = DigitState::INIT;
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

