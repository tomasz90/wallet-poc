#ifndef ABSTRACTSEEDSETTER_H
#define ABSTRACTSEEDSETTER_H

#include <Arduino.h>
#include <array>
#include "bip39/word_list.h"
#include "SeedGenerator.h"

using namespace BIP39;
using std::vector;
using std::array;
using std::string;

class AbstractSeedSetter {
public:
    uint8_t currentIndex;
    word_list mnemonic;

    AbstractSeedSetter(DataHolder *dataHolder);
    bool isSecond() const;
    bool isLast() const;
    void increment();
    void decrement();
    void resetIndex();
};


#endif //ABSTRACTSEEDSETTER_H
