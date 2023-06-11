#include <EEPROM.h>
#include "DataHolder.h"

#define INITIALIZED_ADDRESS 0
#define FAIL_TRIES_ADDRESS 1
#define PIN_ADDRESS 2

int DataHolder::getPinDigit(uint8_t position) {
    return EEPROM.readInt(position + PIN_ADDRESS);
}

void DataHolder::savePin(uint8_t pinCombination[4]) {
    Serial.println("saving pin: " + String(pinCombination[0]) + String(pinCombination[1]) + String(pinCombination[2]) + String(pinCombination[3]));
    // bool initialized
    EEPROM.writeBool(INITIALIZED_ADDRESS, true);
    EEPROM.writeBytes(PIN_ADDRESS, pinCombination, 4);
    EEPROM.commit();
}

void DataHolder::saveFailTryOrReset() {
    int tries = EEPROM.readInt(FAIL_TRIES_ADDRESS);
    tries++;
    Serial.println("Failed try: " + String(tries) + " of 3");
    if (tries >= 3) {
        Serial.println("resetting device");
        tries = 0;
        uint8_t pinReset[4] = {0, 0, 0, 0};
        EEPROM.writeBytes(PIN_ADDRESS, pinReset, 4);
        EEPROM.writeBool(INITIALIZED_ADDRESS, false);
    }
    EEPROM.write(FAIL_TRIES_ADDRESS, tries);
    EEPROM.commit();
}

bool DataHolder::isInitialized() {
    bool init =  EEPROM.readBool(INITIALIZED_ADDRESS);
    Serial.println("isInitialized: " + String(init));
    return init;
}