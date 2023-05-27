#include "pin.h"
#include "Wmath.cpp"

int Pin::currentNumber = random(0, 9);
std::string Pin::pinString = std::string(1, '0' + currentNumber) + " * * *";
int Pin::pinCombination[4];

void Pin::incrementCurrentNumber(int currentIndex) {
    if (currentNumber >= 9) {
        currentNumber = -1;
        pinString[currentIndex * 2] = '<';
    } else {
        currentNumber++;
        pinString[currentIndex * 2] = '0' + currentNumber;
    }
}

void Pin::decrementCurrentNumber(int currentIndex) {
    if (currentNumber <= -1) {
        currentNumber = 9;
        pinString[currentIndex * 2] = '0' + currentNumber;
    } else {
        currentNumber--;
        pinString[currentIndex * 2] = '<';
    }
}

void Pin::setPinAt(int currentIndex) {
    if (currentIndex < 4) {
        int stringIndex = currentIndex * 2;
        pinCombination[currentIndex] = currentNumber;
        currentNumber = random(-1, 9);
        pinString[stringIndex + 2] = '0' + currentNumber;
        pinString[stringIndex] = '$';
    }
}

void Pin::unsetPinAt(int currentIndex) {
    if (currentIndex > 0) {
        int stringIndex = currentIndex * 2;
        currentNumber = pinCombination[currentIndex - 1];
        pinString[stringIndex - 2] = '0' + currentNumber;
        pinString[stringIndex] = '*';
    }
}

int Pin::getCurrentNumber() {
    return currentNumber;
}

const char *Pin::getPinString() {
    return Pin::pinString.c_str();
}

