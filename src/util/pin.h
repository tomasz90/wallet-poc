#include <string>

#ifndef WALLET_POC_PIN_H
#define WALLET_POC_PIN_H

#endif //WALLET_POC_PIN_H


class Pin {
public:
    static const char* getPinString();
    static int getCurrentNumber();
    static void incrementCurrentNumber(int currentIndex);
    static void decrementCurrentNumber(int currentIndex);
    static void setPinAt(int currentIndex);
    static void unsetPinAt(int currentIndex);
private:
    static std::string pinString;
    static int pinCombination[4];
    static int currentNumber;
    static char getCharOfCurrentNumber();
};
