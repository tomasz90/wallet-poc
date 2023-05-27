#include <string>

#ifndef WALLET_POC_PIN_H
#define WALLET_POC_PIN_H

#endif //WALLET_POC_PIN_H


class Pin {
public:
    static std::string pinString;
    static int pinNumber;
    static int pinCombination[4];
    static void unsetPinAt(int currentIndex);
    static const char* getPinString();
    static int currentNumber;
    static void incrementCurrentNumber(int currentIndex);

    static void decrementCurrentNumber(int currentIndex);

    static void setPinAt(int currentIndex);

    static int getCurrentNumber();
};
