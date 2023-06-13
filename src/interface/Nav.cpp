#include "Nav.h"
#include "io/Led.h"
#include "ButtonsHandler.h"
#include "seed/SeedVerifier.h"
#include "io/Signer.h"

using std::string;

Nav::Nav(Disp* disp, SeedViewer* seedViewer, SeedVerifier* seedVerifier, Repository* repository, Pin* pin, Led* led,
         ButtonsHandler &buttonHandler) : led(led), disp(disp), seedViewer(seedViewer), seedVerifier(seedVerifier),
                                          repository(repository), pin(pin), signer(new Signer()), bt(new Bluetooth(this)) {

    //todo: bluetooth can be risky - loop dependency
    buttonHandler.setDebounceTime(10);
    buttonHandler.setCallbacks(
            [this]() { onPrevious(); },
            [this]() { onNext(); },
            [this]() { onBoth(); }
    );
}

void Nav::resetFlags() {
    //todo: flickering problem rethink this
    previousCalled.unset();
    nextCalled.unset();
    bothCalled.unset();
    bothCalledWrapped.unset();
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
        successCalled.set();
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
            successCalled.set();
        } else {
            failureCalled.set();
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
            successCalled.set();
        } else {
            if (repository->getLeftTries() > 1) {
                repository->incrementUsedTries();
                failureCalled.set();
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

void Nav::viewSeed(bool nextHighlighted) {
    if (bothCalled.check()) {
        // CONFIRM SEED PHRASE
        if (nextHighlighted && seedViewer->isLast()) {
            successCalled.set();
            seedViewer->resetIndex();
            return;
        }
        // INCREMENT WORD GO NEXT SCREEN
        else if (nextHighlighted) {
            bothCalledWrapped.set();
            seedViewer->increment();
        }
        // DECREMENT WORD GO FIRST SCREEN
        else if (seedViewer->isSecond()) {
            beginCalled.set();
            seedViewer->decrement();
        }
        // DECREMENT WORD GO PREVIOUS SCREEN
        else {
            bothCalledWrapped.set();
            seedViewer->decrement();
        }
        disp->setTextAtCenter(seedViewer->getCurrentWord(), SEED_WORD_Y_POSITION);
    }
}

void Nav::verifySeed(bool nextHighlighted) {
    checkSerialData();
    if (bothCalled.check()) {
        // CONFIRM SEED PHRASE
        if (nextHighlighted && seedVerifier->isCurrentWordValid() && seedVerifier->isLast()) {
            successCalled.set();
            repository->saveMnemonic(seedVerifier->getMnemonic());
            seedVerifier->resetIndex();
            return;
        }
        // INCREMENT WORD GO NEXT SCREEN
        else if (nextHighlighted && seedVerifier->isCurrentWordValid()) {
            bothCalledWrapped.set();
            seedVerifier->increment();
        }
        // SCREEN NO WORD RECEIVED
        else if (nextHighlighted) {
            disp->blinkTextWarningAtCenter("Need valid word!");
        }
        // DECREMENT WORD GO FIRST SCREEN
        else if (seedVerifier->isSecond()) {
            beginCalled.set();
            seedVerifier->decrement();
        }
        // DECREMENT WORD GO PREVIOUS SCREEN
        else {
            bothCalledWrapped.set();
            seedVerifier->decrement();
        }
        disp->setTextAtCenter(seedVerifier->getCurrentRandomWord(), SEED_WORD_Y_POSITION);
    }
}

void Nav::resetBtBuffer() {
    bt->resetBuffer();
}

void Nav::checkSerialData() {
    string s = bt->receiveData();
    if (s.length() > 0 && !seedVerifier->isCurrentWordValid()) {
        s.erase(std::remove(s.begin(), s.end(), '\"'), s.end());
        if (seedVerifier->validateWord(s)) {
            disp->setTextAtCenter(seedVerifier->getCurrentRandomWord(), SEED_WORD_Y_POSITION);
        } else {
            disp->blinkTextWarningAtCenter("Invalid word!");
        }
    }
}

void Nav::onConnect(BLEServer* pServer) {
    Serial.println("connected");
    btConnectedCalled.set();
    deviceConnected = true;
    connectionTime = millis();
}

void Nav::onDisconnect(BLEServer* pServer) {
    Serial.println("disconnected");
    delete repository->getTx();
    pServer->startAdvertising(); // restart advertising
    btDisconnectedCalled.set();
    deviceConnected = false;
    connectionTime = 0;
}

void Nav::sendAddress() {
    if (deviceConnected && millis() - connectionTime > 2200) {
        string address = repository->getAddress();
        bt->sendAddress(repository->getAddress());
    }
}

void Nav::notifyUninitializedDevice() {
    if (deviceConnected && millis() - connectionTime > 2200) {
        string address = repository->getAddress();
        bt->sendAddress("0x");
    }
}

void Nav::listenTx() {
    if (deviceConnected) {
        string receivedValue = bt->receiveData();
        if (receivedValue.length() > 0) {
            repository->saveTx(new EthTx(receivedValue));
            receivedTxCalled.set();
        }
    }
}

void Nav::signTx() const {
    if (deviceConnected) {
        char* buffer;
        auto key = repository->getPrivateKey();
        auto tx = repository->getTx();
        signer->sign(tx, key, buffer);
        delete tx;
        bt->sendTx(buffer);
    } else {
        Serial.println("Cant sign, device not connected");
    }
}
