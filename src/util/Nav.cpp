#include "Nav.h"
#include "Pin.h"
#include "Led.h"
#include "interface/Disp.h"
#include "ButtonsHandler.h"
#include "SeedGenerator.h"
#include "io/Bluetooth.h"

bool Flag::check() {
    bool temp = flag;
    if (flag) {
        flag = false;
    }
    return temp;
}

void Flag::set() { flag = true; }

void Flag::unset() { flag = false; }

Flag Nav::previousCalled;
Flag Nav::nextCalled;
Flag Nav::bothCalled;

Flag Nav::confirmPinCalled;
Flag Nav::dropPinCalled;
Flag Nav::pinMismatchCalled;

Flag Nav::firstSeedScreenCalled;
Flag Nav::previousSeedScreenCalled;
Flag Nav::nextSeedScreenCalled;
Flag Nav::confirmSeedScreenCalled;
Flag Nav::isValidWordCalled;

Flag Nav::btConnectedCalled;
Flag Nav::btDisconnectedCalled;
Flag Nav::receivedTxCalled;

Led *Nav::led = nullptr;

void Nav::begin(Led *_led, ButtonsHandler &buttonHandler) {
    led = _led;
    buttonHandler.setCallbacks(onPrevious, onNext, onBoth);
}

void Nav::onPrevious() {
    led->flash();
    previousCalled.set();
}

void Nav::onNext() {
    led->flash();
    nextCalled.set();
}

void Nav::onBoth() {
    led->flash();
    bothCalled.set();
}

void Nav::enterPin() {
    // bothCalled.check() needs to be called only once here
    bool _bothCalled = bothCalled.check();

    // INCREMENT DIGIT
    if (nextCalled.check()) {
        Pin::incrementCurrentDigit();
        Disp::drawPin();
    }
    // DECREMENT DIGIT
    else if (previousCalled.check()) {
        Pin::decrementCurrentDigit();
        Disp::drawPin();
    }
    // TRY SET PIN
    else if (_bothCalled && !Pin::isArrow() && Pin::isLastDigit()) {
        Pin::setOneDigit();
        bool saved = Pin::savePin();
        if (saved) { confirmPinCalled.set(); } else { pinMismatchCalled.set(); }
        Pin::clearValues();
    }
    // DROP PIN
    else if (_bothCalled && Pin::isArrow() && Pin::isFirstDigit()) {
        dropPinCalled.set();
        Pin::clearValues();
    }
    // SET DIGIT
    else if (_bothCalled && !Pin::isArrow()) {
        Pin::setOneDigit();
        Disp::drawPin();
    }

    // UNSET DIGIT
    else if (_bothCalled && Pin::isArrow()) {
        Pin::unsetOneDigit();
        Disp::drawPin();
    }
}

void Nav::navigateSeed(bool nextHighlighted) {
    // bothCalled.check() needs to be called only once here
    bool _bothCalled = bothCalled.check();
    bool isValid = true;

    // isValidWordCalled needs to be checked only when both buttons are pressed
    if (SeedGenerator::mode == SeedGeneratorMode::CONFIRM && _bothCalled) {
        isValid = isValidWordCalled.check();
    } else if (SeedGenerator::mode == SeedGeneratorMode::CONFIRM) {
        readSeedWordFromSerial();
    }

    // CONFIRM SEED PHRASE
    if (_bothCalled && nextHighlighted && SeedGenerator::isLast()) {
        confirmSeedScreenCalled.set();
        SeedGenerator::resetIndex();
    }
    // INCREMENT WORD GO NEXT SCREEN
    else if (_bothCalled && nextHighlighted && isValid) {
        nextSeedScreenCalled.set();
        SeedGenerator::increment();
        Disp::clearTextCenter();
    }
    // INCREMENT WORD GO NEXT SCREEN
    else if (_bothCalled && nextHighlighted) {
        Disp::blinkTextWarningAtCenter("Need valid word!");
    }
    // DECREMENT WORD GO FIRST SCREEN
    else if (_bothCalled && SeedGenerator::isSecond()) {
        firstSeedScreenCalled.set();
        SeedGenerator::decrement();
        Disp::clearTextCenter();
    }
    // DECREMENT WORD GO PREVIOUS SCREEN
    else if (_bothCalled) {
        previousSeedScreenCalled.set();
        SeedGenerator::decrement();
        Disp::clearTextCenter();
    }
}

void Nav::readSeedWordFromSerial() {
    std::string incomingString;
    while (Serial.available() > 0) {
        char incomingByte = Serial.read();
        if (incomingByte == '\n') { break; }
        incomingString += incomingByte;
    }
    if (incomingString.length() > 0) {
        bool isValid = SeedGenerator::validateWord(incomingString);
        if (isValid) {
            Nav::isValidWordCalled.set();
            Disp::clearTextCenter();
            Disp::setTextAtCenter(incomingString, 24);
            Disp::disp();
        } else {
            Disp::blinkTextWarningAtCenter("Invalid word!");
        }
    }
}

void Nav::onBtConnected() {
    btConnectedCalled.set();
}

void Nav::onBtDisconnected() {
    Bluetooth::declineTx();
    btDisconnectedCalled.set();
}

void Nav::listenTx() {
    if(Bluetooth::receivedTx()) {
        receivedTxCalled.set();
    }
}
