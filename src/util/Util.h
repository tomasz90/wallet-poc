//
// Created by Tomasz Kulig on 30/05/2023.
//

#ifndef WALLET_POC_UTIL_H
#define WALLET_POC_UTIL_H


#include <stdexcept>
#include <HardwareSerial.h>

void throwException(const String &message) {
    Serial.println("Exception: " + message);
    throw std::runtime_error("Exception thrown");
}

#endif //WALLET_POC_UTIL_H
