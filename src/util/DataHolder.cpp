
#include <EEPROM.h>
#include "DataHolder.h"

void DataHolder::savePin(uint8_t pinCombination[4]) {
    EEPROM.writeBytes(0, pinCombination, 4);
    EEPROM.commit();
}