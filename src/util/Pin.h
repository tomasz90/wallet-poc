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
    static int currentIndex;
    static void begin();
    static std::string getPinString();

    static void incrementCurrentDigit();
    static void decrementCurrentDigit();

    static void setDigit();
    static bool isArrow();

    static void savePin();
    static int rawCombination[4];
private:
    static int savedCombination[4];

    static int _random(int with);
    static void setOneDigit();
    static void unsetOneDigit();
    static char getCharAt(int index);
};
