#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <vector>
#include <string>
#include "bip39/word_list.h"
#include "ethereumHDKeysGenerator/EthereumHDPrivateKey.h"
#include "io/EthTx.h"
#include "const.h"

#define PIN_BYTES_LENGTH 4
#define MNEMONIC_BYTES_LENGTH 107

using std::vector;
using std::array;
using std::string;
using namespace BIP39;

class Repository {
public:
    array<int, MNEMONIC_LENGTH> randomSequence;
    EthTx* tx;
    Repository() = default;
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
    void saveTx(EthTx* _tx);
    EthTx* getTx();
    string getPrivateKey();
    string getAddress();
};


#endif //DATAHOLDER_H
