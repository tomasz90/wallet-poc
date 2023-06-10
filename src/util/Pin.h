#include <string>

#ifndef PIN_H
#define PIN_H

enum class DigitState { UN_INIT, INIT, SET };

enum class PinMode { SET, CONFIRM };

class Pin {
public:
    Pin();
    void clearValues();
    std::string getPinString();
    void incrementCurrentDigit();
    void decrementCurrentDigit();
    bool isArrow();
    bool isFirstDigit();
    bool isLastDigit();
    void unsetOneDigit();
    void setOneDigit();
    bool savePin();
    void setMode(PinMode mode);

private:
    PinMode mode;
    int rawCombination[4];
    int savedCombination[4];
    DigitState stateCombination[4];
    int currentIndex;

    int _random(int with);
    char getCharAt(int index);
};

#endif //PIN_H