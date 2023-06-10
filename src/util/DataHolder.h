#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <vector>
#include <string>
#include "bip39/word_list.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"

#define MNEMONIC_LENGTH 12

using std::vector;
using std::string;
using namespace BIP39;

class DataHolder {
public:
    word_list mnemonic;
    std::array<int, MNEMONIC_LENGTH> randomSequence;
    EthereumHDPrivateKey *account;

    DataHolder() = default;

};


#endif //DATAHOLDER_H
