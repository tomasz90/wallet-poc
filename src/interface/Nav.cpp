#include "Nav.h"
#include "io/Led.h"
#include "ButtonsHandler.h"
#include "util/SeedVerifier.h"

using std::string;

Nav::Nav(Led *_led, ButtonsHandler &buttonHandler, Disp *_disp, SeedVerifier *_seedVerifier, Pin *_pin) {
    led = _led;
    disp = _disp;
    seedVerifier = _seedVerifier;
    pin = _pin;
    buttonHandler.setDebounceTime(10);
    buttonHandler.setCallbacks(
            [this]() { onPrevious(); },
            [this]() { onNext(); },
            [this]() { onBoth(); }
    );
}

void Nav::resetFlags() {
    previousCalled.unset();
    nextCalled.unset();
    bothCalled.unset();
    confirmPinCalled.unset();
    dropPinCalled.unset();
    pinMismatchCalled.unset();
    firstSeedScreenCalled.unset();
    previousSeedScreenCalled.unset();
    nextSeedScreenCalled.unset();
    confirmSeedScreenCalled.unset();
    isValidWordCalled.unset();
    btConnectedCalled.unset();
    btDisconnectedCalled.unset();
    receivedTxCalled.unset();
}

void Nav::setBt(Bluetooth *_bt) {
    bt = _bt;
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
        pin->incrementCurrentDigit();
        disp->drawPin(pin->getPinString());
    }
        // DECREMENT DIGIT
    else if (previousCalled.check()) {
        pin->decrementCurrentDigit();
        disp->drawPin(pin->getPinString());
    }
        // TRY SET PIN
    else if (_bothCalled && !pin->isArrow() && pin->isLastDigit()) {
        pin->setOneDigit();
        bool saved = pin->savePin();
        if (saved) { confirmPinCalled.set(); } else { pinMismatchCalled.set(); }
        pin->clearValues();
    }
        // DROP PIN
    else if (_bothCalled && pin->isArrow() && pin->isFirstDigit()) {
        dropPinCalled.set();
        pin->clearValues();
    }
        // SET DIGIT
    else if (_bothCalled && !pin->isArrow()) {
        pin->setOneDigit();
        disp->drawPin(pin->getPinString());
    }

        // UNSET DIGIT
    else if (_bothCalled && pin->isArrow()) {
        pin->unsetOneDigit();
        disp->drawPin(pin->getPinString());
    }
}

void Nav::navigateSeed(bool nextHighlighted) {
    if (bothCalled.check()) {
        // CONFIRM SEED PHRASE
        if (nextHighlighted && seedVerifier->isLast()) {
            confirmSeedScreenCalled.set();
            seedVerifier->resetIndex();
        }
        // INCREMENT WORD GO NEXT SCREEN
        else if (nextHighlighted) {
            nextSeedScreenCalled.set();
            seedVerifier->increment();
            disp->setTextAtCenter(seedVerifier->getCurrentWord(), 24);
        }
        // DECREMENT WORD GO FIRST SCREEN
        else if (seedVerifier->isSecond()) {
            firstSeedScreenCalled.set();
            seedVerifier->decrement();
            disp->setTextAtCenter(seedVerifier->getCurrentWord(), 24);
        }
        // DECREMENT WORD GO PREVIOUS SCREEN
        else  {
            previousSeedScreenCalled.set();
            seedVerifier->decrement();
            disp->setTextAtCenter(seedVerifier->getCurrentWord(), 24);
        }
    }
}

void Nav::navigateSeedConfirm(bool nextHighlighted) {
    DataType type = checkSerialData();

    if (bothCalled.check()) {
        Serial.println(("type: " + std::to_string(static_cast<int>(type))).c_str());
        // CONFIRM SEED PHRASE
        if (nextHighlighted && type == DataType::VALID && seedVerifier->isLast()) {
            confirmSeedScreenCalled.set();
            seedVerifier->resetIndex();
        }
        // INCREMENT WORD GO NEXT SCREEN
        else if (nextHighlighted && type == DataType::VALID) {
            nextSeedScreenCalled.set();
            disp->setTextAtCenter(seedVerifier->getCurrentRandomWord(), 24);
            seedVerifier->increment();
        }
        // SCREEN INVALID WORD
        else if (nextHighlighted && type == DataType::INVALID) {
            disp->blinkTextWarningAtCenter("Invalid word!");
        }
        // SCREEN NO WORD RECEIVED
        else if (nextHighlighted) {
            disp->blinkTextWarningAtCenter("Need valid word!");
        }
        // DECREMENT WORD GO FIRST SCREEN
        else if (seedVerifier->isSecond()) {
            firstSeedScreenCalled.set();
            seedVerifier->decrement();
            disp->setTextAtCenter(seedVerifier->getCurrentRandomWord(), 24);
        }
        // DECREMENT WORD GO PREVIOUS SCREEN
        else {
            previousSeedScreenCalled.set();
            seedVerifier->decrement();
            disp->setTextAtCenter(seedVerifier->getCurrentRandomWord(), 24);
        }
    }
}

DataType Nav::checkSerialData() {
    string s;
    while (Serial.available() > 0) {
        char incomingByte = Serial.read();
        if (incomingByte == '\n') { break; }
        s += incomingByte;
    }
    if (s.length() > 0 && seedVerifier->validateWord(s)) {
        return DataType::VALID;
    } else if (s.length() > 0) {
        return DataType::INVALID;
    } else {
        return DataType::NONE;
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
    bt->declineTx();
    pServer->startAdvertising(); // restart advertising
    btDisconnectedCalled.set();
    deviceConnected = false;
}

void Nav::sendAddress() {
    if (deviceConnected && btConnectedCalledPrivate.check()) {
        delay(2000);
        bt->sendAddress();
    }
}

void Nav::listenTx() {
    if (deviceConnected) {
        if (bt->receivedTx()) {
            receivedTxCalled.set();
        }
    }
}

void Nav::signTx() const {
    if (deviceConnected) {
        bt->signTx();
    } else {
        Serial.println("Cant sign, device not connected");
    }
}
