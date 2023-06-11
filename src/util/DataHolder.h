#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <vector>
#include <string>
#include "bip39/word_list.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"
#include "io/EthTx.h"

#define MNEMONIC_LENGTH 12

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
    void savePin(uint8_t pinCombination[4]);
    void saveTries(uint8_t tries);
};


#endif //DATAHOLDER_H
