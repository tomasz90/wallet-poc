#include <EEPROM.h>
#include <cstring>
#include "Repository.h"
#include "utility/trezor/memzero.h"

#define INITIALIZED_ADDRESS 0
#define FAIL_TRIES_ADDRESS 1
#define PIN_ADDRESS 2
#define MNEMONIC_ADDRESS 6

#define DEFAULT_PATH "m/44'/60'/0'/0/0"

void Repository::getPin(uint8_t pinCombination[4]) {
    EEPROM.readBytes(PIN_ADDRESS, pinCombination, 4);
}

void Repository::savePin(uint8_t pinCombination[4]) {
    Serial.println("saving pin: " + String(pinCombination[0]) + String(pinCombination[1]) + String(pinCombination[2]) +
                   String(pinCombination[3]));
    EEPROM.writeBytes(PIN_ADDRESS, pinCombination, 4);
    EEPROM.commit();
}

std::string Repository::getMnemonic() const {
    char _mnemonic[MNEMONIC_BYTES_LENGTH];
    EEPROM.readBytes(MNEMONIC_ADDRESS, _mnemonic, MNEMONIC_BYTES_LENGTH);

    // CONVERT TO STRING
    std::string str;
    for (auto &i: _mnemonic) {
        str += i;
    }

    // REMOVE TRAILING SPACES
    std::size_t lastNonSpace = str.find_last_not_of(' ');
    if (lastNonSpace != std::string::npos) {
        str = str.substr(0, lastNonSpace + 1);
    }

    memzero(_mnemonic, MNEMONIC_BYTES_LENGTH);
    return str;
}

void Repository::saveMnemonic(const std::string &mnemonicStr) const {
    char _mnemonic[MNEMONIC_BYTES_LENGTH];
    // FILL WITH SPACES
    std::memset(_mnemonic, ' ', MNEMONIC_BYTES_LENGTH);

    // COPY MNEMONIC TO CHAR ARRAY
    std::size_t length = mnemonicStr.length();
    std::strncpy(_mnemonic, mnemonicStr.c_str(), length);
    EEPROM.writeBool(INITIALIZED_ADDRESS, true);
    EEPROM.writeBytes(MNEMONIC_ADDRESS, _mnemonic, MNEMONIC_BYTES_LENGTH);
    EEPROM.commit();
}

uint8_t Repository::getLeftTries() {
    return 3 - EEPROM.readUChar(FAIL_TRIES_ADDRESS);
}

void Repository::resetTries() {
    EEPROM.writeUChar(FAIL_TRIES_ADDRESS, 0);
    EEPROM.commit();
}

void Repository::incrementUsedTries() {
    uint8_t tries = EEPROM.readUChar(FAIL_TRIES_ADDRESS);
    tries++;
    EEPROM.writeUChar(FAIL_TRIES_ADDRESS, tries);
    EEPROM.commit();
}

void Repository::resetDevice() {
    Serial.println("resetting device");
    uint8_t zeroPin[4] = {0, 0, 0, 0};
    char zeroMnemonic[MNEMONIC_BYTES_LENGTH];
    memzero(zeroMnemonic, MNEMONIC_BYTES_LENGTH);
    EEPROM.writeBytes(MNEMONIC_ADDRESS, zeroMnemonic, MNEMONIC_BYTES_LENGTH);
    EEPROM.writeBytes(PIN_ADDRESS, zeroPin, PIN_BYTES_LENGTH);
    EEPROM.writeBool(INITIALIZED_ADDRESS, false);
    EEPROM.writeUChar(FAIL_TRIES_ADDRESS, 0);
    EEPROM.commit();
}

bool Repository::isInitialized() {
    return EEPROM.readBool(INITIALIZED_ADDRESS);
}

void Repository::printInfo() {
    uint8_t pin[4];
    EEPROM.readBytes(PIN_ADDRESS, pin, 4);
    uint8_t failTries = EEPROM.readUChar(FAIL_TRIES_ADDRESS);

    Serial.println("Initialized: " + String(isInitialized()));
    Serial.println("Failed tries: " + String(failTries));
    Serial.printf("PIN: %d%d%d%d\n", pin[0], pin[1], pin[2], pin[3]);
}

void Repository::saveTx(EthTx* _tx) {
    tx = _tx;
}

EthTx* Repository::getTx() {
    return tx;
}

string Repository::getPrivateKey() {
    EthereumHDPrivateKey hd(getMnemonic());
    EthereumHDPrivateKey* firstAccount = hd.derive(DEFAULT_PATH);
    string privateKey = firstAccount->prv().c_str();
    delete firstAccount;
    return privateKey;
}

string Repository::getAddress() {
    EthereumHDPrivateKey hd(getMnemonic());
    EthereumHDPrivateKey* firstAccount = hd.derive(DEFAULT_PATH);
    string address = firstAccount->addressChecksumed().c_str();
    delete firstAccount;
    return address;
}
