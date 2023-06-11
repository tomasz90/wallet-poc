
#include <EEPROM.h>
#include "DataHolder.h"

void DataHolder::savePin(uint8_t pinCombination[4]) {
    // bool initialized
    EEPROM.writeBool(0, true);
    EEPROM.writeBytes(1, pinCombination, 4);
    EEPROM.commit();
}

void DataHolder::saveTryOrReset() {
    int tries = EEPROM.readInt(5);
    tries++;
    if (tries > 3) {
        tries = 0;
        uint8_t pinReset[4] = {0, 0, 0, 0};
        EEPROM.writeBytes(1, pinReset, 4);
        EEPROM.writeBool(0, false);
    }
    EEPROM.write(5, tries);
    EEPROM.commit();
}

bool DataHolder::isInitialized() {
    return EEPROM.readBool(0);
}