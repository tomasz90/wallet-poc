#include "Nav.h"
#include "Pin.h"
#include "Led.h"
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

Nav::Nav(Led *_led, ButtonsHandler &buttonHandler, Disp *_disp, SeedGenerator *_seedGenerator) {
    led = _led;
    disp = _disp;
    seedGenerator = _seedGenerator;
    buttonHandler.setCallbacks(
            [this]() { onPrevious(); },
            [this]() { onNext(); },
            [this]() { onBoth(); }
    );
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
        disp->drawPin(Pin::getPinString());
    }
        // DECREMENT DIGIT
    else if (previousCalled.check()) {
        Pin::decrementCurrentDigit();
        disp->drawPin(Pin::getPinString());
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
        disp->drawPin(Pin::getPinString());
    }

        // UNSET DIGIT
    else if (_bothCalled && Pin::isArrow()) {
        Pin::unsetOneDigit();
        disp->drawPin(Pin::getPinString());
    }
}

void Nav::navigateSeed(bool nextHighlighted) {
    // bothCalled.check() needs to be called only once here
    bool _bothCalled = bothCalled.check();
    bool isValid = true;

    // isValidWordCalled needs to be checked only when both buttons are pressed
    if (seedGenerator->mode == SeedGeneratorMode::CONFIRM && _bothCalled) {
        isValid = isValidWordCalled.check();
    } else if (seedGenerator->mode == SeedGeneratorMode::CONFIRM) {
        readSeedWordFromSerial();
    }

    // CONFIRM SEED PHRASE
    if (_bothCalled && nextHighlighted && seedGenerator->isLast()) {
        confirmSeedScreenCalled.set();
        seedGenerator->resetIndex();
    }
    // INCREMENT WORD GO NEXT SCREEN
    else if (_bothCalled && nextHighlighted && isValid) {
        nextSeedScreenCalled.set();
        seedGenerator->increment();
        disp->clearTextCenter();
    }
    // INCREMENT WORD GO NEXT SCREEN
    else if (_bothCalled && nextHighlighted) {
        disp->blinkTextWarningAtCenter("Need valid word!");
    }
    // DECREMENT WORD GO FIRST SCREEN
    else if (_bothCalled && seedGenerator->isSecond()) {
        firstSeedScreenCalled.set();
        seedGenerator->decrement();
        disp->clearTextCenter();
    }
    // DECREMENT WORD GO PREVIOUS SCREEN
    else if (_bothCalled) {
        previousSeedScreenCalled.set();
        seedGenerator->decrement();
        disp->clearTextCenter();
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
        bool isValid = seedGenerator->validateWord(incomingString);
        if (isValid) {
            Nav::isValidWordCalled.set();
            disp->clearTextCenter();
            disp->setTextAtCenter(incomingString, 24);
            disp->disp();
        } else {
            disp->blinkTextWarningAtCenter("Invalid word!");
        }
    }
}

void Nav::onConnect(BLEServer *pServer) {
    Serial.println("connected");
    btConnectedCalled.set();
    btConnectedCalledPrivate.set();
    deviceConnected = true;
}

void Nav::onDisconnect(BLEServer *pServer) {
    Serial.println("disconnected");
    Bluetooth::declineTx();
    pServer->startAdvertising(); // restart advertising
    btDisconnectedCalled.set();
    deviceConnected = false;
}

void Nav::sendAddress() {
    if (deviceConnected && btConnectedCalledPrivate.check()) {
        delay(2000);
        Bluetooth::sendAddress();
    }
}

void Nav::listenTx() {
    if (deviceConnected) {
        if (Bluetooth::receivedTx()) {
            receivedTxCalled.set();
        }
    }
}

void Nav::signTx() const {
    if (deviceConnected) {
        Bluetooth::signTx();
    } else {
        Serial.println("Cant sign, device not connected");
    }
}
