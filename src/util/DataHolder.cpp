#include <EEPROM.h>
#include <cstring>
#include "DataHolder.h"
#include "utility/trezor/memzero.h"

#define INITIALIZED_ADDRESS 0
#define FAIL_TRIES_ADDRESS 1
#define PIN_ADDRESS 2
#define MNEMONIC_ADDRESS 6

void DataHolder::getPin(uint8_t pinCombination[4]) {
    EEPROM.readBytes(PIN_ADDRESS, pinCombination, 4);
}

void DataHolder::savePin(uint8_t pinCombination[4]) {
    Serial.println("saving pin: " + String(pinCombination[0]) + String(pinCombination[1]) + String(pinCombination[2]) +
                   String(pinCombination[3]));
    // bool initialized
    EEPROM.writeBool(INITIALIZED_ADDRESS, true);
    EEPROM.writeBytes(PIN_ADDRESS, pinCombination, 4);
    EEPROM.commit();
}

std::string DataHolder::getMnemonic() const {
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

void DataHolder::saveMnemonic(const std::string &mnemonicStr) const {
    char _mnemonic[MNEMONIC_BYTES_LENGTH];
    // FILL WITH SPACES
    std::memset(_mnemonic, ' ', MNEMONIC_BYTES_LENGTH);

    // COPY MNEMONIC TO CHAR ARRAY
    std::size_t length = mnemonicStr.length();
    std::strncpy(_mnemonic, mnemonicStr.c_str(), length);

    EEPROM.writeBytes(MNEMONIC_ADDRESS, _mnemonic, MNEMONIC_BYTES_LENGTH);
    EEPROM.commit();
}

uint8_t DataHolder::getLeftTries() {
    return 3 - EEPROM.readUChar(FAIL_TRIES_ADDRESS);
}

void DataHolder::resetTries() {
    EEPROM.writeUChar(FAIL_TRIES_ADDRESS, 0);
    EEPROM.commit();
}

void DataHolder::incrementUsedTries() {
    uint8_t tries = EEPROM.readUChar(FAIL_TRIES_ADDRESS);
    tries++;
    EEPROM.writeUChar(FAIL_TRIES_ADDRESS, tries);
    EEPROM.commit();
}

void DataHolder::resetDevice() {
    Serial.println("resetting device");
    uint8_t pinReset[4] = {0, 0, 0, 0};
    EEPROM.writeBytes(PIN_ADDRESS, pinReset, 4);
    EEPROM.writeBool(INITIALIZED_ADDRESS, false);
    EEPROM.writeUChar(FAIL_TRIES_ADDRESS, 0);
    EEPROM.commit();
}

bool DataHolder::isInitialized() {
    return EEPROM.readBool(INITIALIZED_ADDRESS);
}

void DataHolder::printInfo() {
    uint8_t pin[4];
    EEPROM.readBytes(PIN_ADDRESS, pin, 4);
    uint8_t failTries = EEPROM.readUChar(FAIL_TRIES_ADDRESS);

    Serial.println("Initialized: " + String(isInitialized()));
    Serial.println("Failed tries: " + String(failTries));
    Serial.printf("PIN: %d%d%d%d\n", pin[0], pin[1], pin[2], pin[3]);
}
