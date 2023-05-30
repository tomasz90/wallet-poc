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
    static void begin();
    static std::string getPinString();
    static void incrementCurrentDigit();
    static void decrementCurrentDigit();
    static void setOrUnsetDigit();
    static void savePin();
    static bool ifLastDigit();
    static bool ifFirstDigit();
private:

    static int currentIndex;
    static int rawCombination[4];
    static int savedCombination[4];

    static int _random(int with);
    static char getCharAt(int index);
    static bool isArrow();
    static void setOneDigit();
    static void unsetOneDigit();
};
