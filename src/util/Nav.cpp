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
    else if (_bothCalled && !Pin::isArrow() && Pin::ifLastDigit()) {
        Pin::setOneDigit();
        bool saved = Pin::savePin();
        if (saved) { confirmPinCalled.set(); } else { pinMismatchCalled.set(); }
        Pin::clearValues();
    }
    // DROP PIN
    else if (_bothCalled && Pin::isArrow() && Pin::ifFirstDigit()) {
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