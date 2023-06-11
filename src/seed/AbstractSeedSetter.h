#ifndef ABSTRACTSEEDSETTER_H
#define ABSTRACTSEEDSETTER_H

#include <Arduino.h>
#include <array>
#include "bip39/word_list.h"

using namespace BIP39;
using std::vector;
using std::array;
using std::string;

class AbstractSeedSetter {
public:
    uint8_t currentIndex;

    AbstractSeedSetter();
    bool isSecond() const;
    bool isLast() const;
    void increment();
    void decrement();
    void resetIndex();
    void setMnemonic(word_list &tempMnemonic);
protected:
    word_list tempMnemonic;
};


#endif //ABSTRACTSEEDSETTER_H
