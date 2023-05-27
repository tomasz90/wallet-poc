#include <HardwareSerial.h>
#include "pin.h"
#include "Wmath.cpp"

int Pin::currentNumber = random(0, 9);
std::string Pin::pinString = std::string(1, '0' + currentNumber) + " * * *";
int Pin::pinCombination[4];

const char *Pin::getPinString() {
    return Pin::pinString.c_str();
}

int Pin::getCurrentNumber() {
    return currentNumber;
}

void Pin::incrementCurrentNumber(int currentIndex) {
    if (currentNumber >= 9) {
        currentNumber = -1;
    } else {
        currentNumber++;
    }
    pinString[currentIndex * 2] = getCharOfCurrentNumber();
    Serial.println(currentNumber);
}

void Pin::decrementCurrentNumber(int currentIndex) {
    if (currentNumber >= 0) {
        currentNumber--;
    } else {
        currentNumber = 9;
    }
    pinString[currentIndex * 2] = getCharOfCurrentNumber();
    Serial.println(currentNumber);
}

char Pin::getCharOfCurrentNumber() {
    if(currentNumber > -1) {
        return '0' + currentNumber;
    } else {
        return '<';
    }
}

void Pin::setPinAt(int currentIndex) {
    if (currentIndex < 4) {
        int stringIndex = currentIndex * 2;
        pinCombination[currentIndex] = currentNumber;
        currentNumber = random(-1, 9);
        pinString[stringIndex] = '$';
        pinString[stringIndex + 2] = getCharOfCurrentNumber();
    }
}

void Pin::unsetPinAt(int currentIndex) {
    if (currentIndex > 0) {
        int stringIndex = currentIndex * 2;
        currentNumber = pinCombination[currentIndex - 1];
        pinString[stringIndex] = '*';
        pinString[stringIndex - 2] = getCharOfCurrentNumber();
    }
}

