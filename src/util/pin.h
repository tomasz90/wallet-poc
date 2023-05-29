#include <string>

#ifndef WALLET_POC_PIN_H
#define WALLET_POC_PIN_H

#endif //WALLET_POC_PIN_H


class Pin {
public:
    static const char* getPinString();
    static void incrementCurrentNumber(int _currentIndex);
    static void decrementCurrentNumber(int _currentIndex);
    static void setPinNumber();
    static void unsetPinNumber();
    static int isArrow();

private:
    static int currentIndex;
    static int currentNumber;
    static std::string pinString;
    static int pinCombination[4];

    static char getCharOfCurrentNumber();

};
