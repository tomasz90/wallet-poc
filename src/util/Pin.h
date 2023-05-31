#include <string>

#ifndef WALLET_POC_PIN_H
#define WALLET_POC_PIN_H

#endif //WALLET_POC_PIN_H

enum class DigitState { UN_INIT, INIT, SET };

enum class PinMode { SET, CONFIRM };

class Pin {
public:
    static void clearValues();
    static void setMode(PinMode mode);
    static std::string getPinString();
    static void incrementCurrentDigit();
    static void decrementCurrentDigit();

    static bool isArrow();
    static void unsetOneDigit();
    static void setOneDigit();

    static bool savePin();
    static bool ifLastDigit();
    static bool ifFirstDigit();

private:
    static PinMode mode;
    static int rawCombination[4];
    static int savedCombination[4];
    static int currentIndex;

    static int _random(int with);
    static char getCharAt(int index);

};
