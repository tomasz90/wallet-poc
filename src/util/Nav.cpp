#include "Nav.h"
#include "Pin.h"
#include "Led.h"
#include "interface/Disp.h"
#include "ButtonsHandler.h"

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
Flag Nav::nextPinBothCalled;
Flag Nav::previousPinBothCalled;
Flag Nav::pinMismatch;

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
    if (nextCalled.check()) {
        Pin::incrementCurrentDigit();
        Disp::drawPin();
    } else if (previousCalled.check()) {
        Pin::decrementCurrentDigit();
        Disp::drawPin();
    } else if (bothCalled.check()) {
        if (Pin::ifFirstDigit()) {
            previousPinBothCalled.set();
        } else if (Pin::ifLastDigit()) {
            Pin::setOrUnsetDigit();
            bool saved = Pin::savePin(); // todo: check if this is called only once
            if(saved) {
                nextPinBothCalled.set();
            } else {
                pinMismatch.set();
            }
        } else {
            Pin::setOrUnsetDigit();
            Disp::drawPin();
        }
    }
}