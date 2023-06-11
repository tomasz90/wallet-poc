
#include <EEPROM.h>
#include "DataHolder.h"

void DataHolder::savePin(uint8_t pinCombination[4]) {
    EEPROM.writeBytes(0, pinCombination, 4);
    EEPROM.commit();
}

void DataHolder::saveTries(uint8_t tries) {
    EEPROM.write(5, tries);
}