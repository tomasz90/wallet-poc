#include <string>

#ifndef WALLET_POC_PIN_H
#define WALLET_POC_PIN_H

#endif //WALLET_POC_PIN_H

enum class DigitState {
    UN_INIT,
    INIT,
    SET
};

class Pin {
public:
    static std::string getPinString();
    static void incrementCurrentNumber();
    static void decrementCurrentNumber();
    static void setOneDigit();
    static void unsetOneDigit();
    static int isArrow();

    static int currentIndex;
private:
    static int pinCombination[4];
    static char getCharAt(int index);
    static int _random(int with);
};
