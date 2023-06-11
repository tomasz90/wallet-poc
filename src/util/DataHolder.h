#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <vector>
#include <string>
#include "bip39/word_list.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"
#include "io/EthTx.h"

#define MNEMONIC_LENGTH 12

#define PIN_BYTES_LENGTH 4
#define MNEMONIC_BYTES_LENGTH 107

using std::vector;
using std::array;
using std::string;
using namespace BIP39;

class DataHolder {
public:
    word_list mnemonic;
    array<int, MNEMONIC_LENGTH> randomSequence;
    EthereumHDPrivateKey *account;
    EthTx* tx;
    DataHolder() = default;
    bool isInitialized();
    void getPin(uint8_t pinCombination[PIN_BYTES_LENGTH]);
    void savePin(uint8_t pinCombination[PIN_BYTES_LENGTH]);
    uint8_t getLeftTries();
    void printInfo();
    void resetTries();
    void incrementUsedTries();
    void resetDevice();
    std::string getMnemonic() const;
    void saveMnemonic(const std::string &mnemonic) const;
};


#endif //DATAHOLDER_H
