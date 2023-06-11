#include <string>

#ifndef PIN_H
#define PIN_H

enum class DigitState { UN_INIT, INIT, SET };

class Pin {
public:
    uint8_t savedCombination[4];

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
    void setPin();
    bool confirmPin();
    bool unlockPin(uint8_t pinFromFlash[4]);
private:
    int currentIndex;
    int rawCombination[4];
    DigitState stateCombination[4];

    int _random(int with);
    char getCharAt(int index);
    void assignArray(uint8_t *saved, const int *raw);
    bool areTheSame(const uint8_t *saved, const int *raw);
};

#endif //PIN_H