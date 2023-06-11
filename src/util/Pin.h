#include <string>
#include "DataHolder.h"

#ifndef PIN_H
#define PIN_H

enum class DigitState { UN_INIT, INIT, SET };

enum class PinMode { SET, CONFIRM, UNLOCK };

class Pin {
public:
    PinMode mode;

    Pin(DataHolder *dataHolder);
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
    DataHolder *dataHolder;
    int currentIndex;
    int rawCombination[4];
    uint8_t savedCombination[4];
    DigitState stateCombination[4];

    int _random(int with);
    char getCharAt(int index);
    void assignArray(uint8_t *saved, const int *raw);
    bool areTheSame(const uint8_t *saved, const int *raw);
};

#endif //PIN_H