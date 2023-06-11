#include "Nav.h"
#include "io/Led.h"
#include "ButtonsHandler.h"
#include "seed/SeedVerifier.h"

using std::string;

Nav::Nav(Led *_led,
         ButtonsHandler &buttonHandler,
         Disp *_disp,
         SeedViewer *_seedViewer,
         SeedVerifier *_seedVerifier,
         Repository *_repository,
         Pin *_pin) {
    led = _led;
    disp = _disp;
    seedViewer = _seedViewer;
    seedVerifier = _seedVerifier;
    repository = _repository;
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

void Nav::setPin() {
    // bothCalled.check() needs to be called only once here
    bool _bothCalled = bothCalled.check();

    // TRY SET PIN
    if (_bothCalled && !pin->isArrow() && pin->isLastDigit()) {
        pin->setOneDigit();
        pin->setPin();
        confirmPinCalled.set();
        pin->clearValues();
        return;
    }
    enterPin(_bothCalled);
}

void Nav::confirmPin() {
    // bothCalled.check() needs to be called only once here
    bool _bothCalled = bothCalled.check();

    // TRY CONFIRM PIN
    if (_bothCalled && !pin->isArrow() && pin->isLastDigit()) {
        pin->setOneDigit();
        if (pin->confirmPin()) {
            repository->savePin(pin->savedCombination);
            confirmPinCalled.set();
        } else {
            pinMismatchCalled.set();
        }
        pin->clearValues();
        return;
    }
    enterPin(_bothCalled);
}

void Nav::unlockPin() {
    // bothCalled.check() needs to be called only once here
    bool _bothCalled = bothCalled.check();

    // TRY UNLOCK PIN
    if (_bothCalled && !pin->isArrow() && pin->isLastDigit()) {
        pin->setOneDigit();
        uint8_t pinFromFlash[4];
        repository->getPin(pinFromFlash);
        if (pin->unlockPin(pinFromFlash)) {
            repository->resetTries();
            confirmPinCalled.set();
        } else {
            if (repository->getLeftTries() > 1) {
                repository->incrementUsedTries();
                pinMismatchCalled.set();
            } else {
                repository->resetDevice();
                resetDeviceCalled.set();
            }
        }
        pin->clearValues();
        return;
    }
    enterPin(_bothCalled);
}

void Nav::enterPin(bool _bothCalled) {
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
        if (nextHighlighted && seedViewer->isLast()) {
            confirmSeedScreenCalled.set();
            seedViewer->resetIndex();
            return;
        }
        // INCREMENT WORD GO NEXT SCREEN
        else if (nextHighlighted) {
            nextSeedScreenCalled.set();
            seedViewer->increment();
        }
        // DECREMENT WORD GO FIRST SCREEN
        else if (seedViewer->isSecond()) {
            firstSeedScreenCalled.set();
            seedViewer->decrement();
        }
        // DECREMENT WORD GO PREVIOUS SCREEN
        else {
            previousSeedScreenCalled.set();
            seedViewer->decrement();
        }
        disp->setTextAtCenter(seedViewer->getCurrentWord(), SEED_WORD_Y_POSITION);
    }
}

void Nav::navigateSeedConfirm(bool nextHighlighted) {
    checkSerialData();
    if (bothCalled.check()) {
        // CONFIRM SEED PHRASE
        if (nextHighlighted && seedVerifier->isCurrentWordValid() && seedVerifier->isLast()) {
            confirmSeedScreenCalled.set();
            seedVerifier->resetIndex();
            return;
        }
        // INCREMENT WORD GO NEXT SCREEN
        else if (nextHighlighted && seedVerifier->isCurrentWordValid()) {
            nextSeedScreenCalled.set();
            seedVerifier->increment();
        }
        // SCREEN NO WORD RECEIVED
        else if (nextHighlighted) {
            disp->blinkTextWarningAtCenter("Need valid word!");
        }
        // DECREMENT WORD GO FIRST SCREEN
        else if (seedVerifier->isSecond()) {
            firstSeedScreenCalled.set();
            seedVerifier->decrement();
        }
        // DECREMENT WORD GO PREVIOUS SCREEN
        else {
            previousSeedScreenCalled.set();
            seedVerifier->decrement();
        }
        disp->setTextAtCenter(seedVerifier->getCurrentRandomWord(), SEED_WORD_Y_POSITION);
    }
}

void Nav::checkSerialData() {
    string s;
    while (Serial.available() > 0) {
        char incomingByte = Serial.read();
        if (incomingByte == '\n') { break; }
        s += incomingByte;
    }
    if (s.length() > 0 && !seedVerifier->isCurrentWordValid()) {
        if (seedVerifier->validateWord(s)) {
            disp->setTextAtCenter(seedVerifier->getCurrentRandomWord(), SEED_WORD_Y_POSITION);
        } else {
            disp->blinkTextWarningAtCenter("Invalid word!");
        }
    }
}

void Nav::onConnect(BLEServer *pServer) {
    Serial.println("connected");
    btConnectedCalled.set();
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
    if (deviceConnected) {
        delay(2200);
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
