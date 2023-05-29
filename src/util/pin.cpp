#include "pin.h"
#include "Wmath.cpp"

int Pin::currentNumber = random(0, 9);
int Pin::currentIndex = 0;
std::string Pin::pinString = std::string(1, '0' + currentNumber) + " * * *";
int Pin::pinCombination[4];

const char *Pin::getPinString() {
    return Pin::pinString.c_str();
}

int Pin::isArrow() {
    return currentNumber == -1;
}

void Pin::incrementCurrentNumber(int _currentIndex) {
    if (currentNumber >= 9) {
        if (currentIndex == 0) {
            currentNumber = 0;
        } else {
            currentNumber = -1;
        }
    } else {
        currentNumber++;
    }
    pinString[_currentIndex * 2] = getCharOfCurrentNumber();
}

void Pin::decrementCurrentNumber(int _currentIndex) {
    if (currentNumber == 0) {
        if (currentIndex == 0) {
            currentNumber = 9;
        } else {
            currentNumber = -1;
        }
    } else if(currentNumber == -1) {
            currentNumber = 9;
    } else {
        currentNumber--;
    }
    pinString[_currentIndex * 2] = getCharOfCurrentNumber();
}

char Pin::getCharOfCurrentNumber() {
    if (currentNumber > -1) {
        return '0' + currentNumber;
    } else {
        return '<';
    }
}

void Pin::setPinNumber() {
    if (currentIndex == 3) {
        currentIndex = 0;
        currentNumber = random(0, 9);
        pinString = std::string(1, '0' + currentNumber) + " * * *";
        // todo: remember pin combination
    } else if (currentIndex < 4) {
        int stringIndex = currentIndex * 2;
        pinCombination[currentIndex] = currentNumber;
        currentNumber = random(-1, 9);
        pinString[stringIndex] = '$';
        pinString[stringIndex + 2] = getCharOfCurrentNumber();
        currentIndex++;
    }
}

void Pin::unsetPinNumber() {
    if (currentIndex > 0) {
        int stringIndex = currentIndex * 2;
        currentNumber = pinCombination[currentIndex - 1];
        pinString[stringIndex] = '*';
        pinString[stringIndex - 2] = getCharOfCurrentNumber();
        currentIndex--;
    }
}

