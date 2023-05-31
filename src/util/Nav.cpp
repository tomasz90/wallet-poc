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

Flag Nav::confirmPinCalled;
Flag Nav::dropPinCalled;
Flag Nav::pinMismatchCalled;

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
        if (Pin::ifFirstDigitIsArrow()) {
            dropPinCalled.set();
        } else if (Pin::ifLastDigitIsDigit()) {
            Pin::setOrUnsetDigit();
            bool saved = Pin::savePin();
            if(saved) {
                confirmPinCalled.set();
            } else {
                pinMismatchCalled.set();
            }
        } else {
            Pin::setOrUnsetDigit();
            Disp::drawPin();
        }
    }
}