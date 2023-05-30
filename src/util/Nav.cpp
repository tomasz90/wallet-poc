#include "Nav.h"
#include "Pin.h"
#include "Led.h"
#include "interface/Disp.h"
#include "ButtonsHandler.h"

bool Nav::previousCalled = false;
bool Nav::nextCalled = false;
bool Nav::bothCalled = false;

bool Nav::nextPinBothCalled = false;
bool Nav::previousPinBothCalled = false;

Led *Nav::led = nullptr;

void Nav::begin(Led *_led, ButtonsHandler &buttonHandler) {
    led = _led;
    buttonHandler.setCallbacks(onPrevious, onNext, onBoth);
}

void Nav::onPrevious() {
    led->flash();
    previousCalled = true;
}

void Nav::onNext() {
    led->flash();
    nextCalled = true;
}

void Nav::onBoth() {
    led->flash();
    bothCalled = true;
}

std::function<bool()> Nav::_(bool &called) {
    return [&called]() -> bool {
        if (called) {
            called = false;
            return true;
        }
        return false;
    };
}

void Nav::enterPin() {
    if (_(nextCalled)) {
        Pin::incrementCurrentDigit();
        Disp::drawPin();
    } else if (_(previousCalled)) {
        Pin::decrementCurrentDigit();
        Disp::drawPin();
    } else if (_(bothCalled)) {
        if(Pin::ifFirstDigit()) {
            previousPinBothCalled = true;
        } else if(Pin::ifLastDigit()) {
            Pin::setOrUnsetDigit();
            Pin::savePin();
            nextPinBothCalled = true;
        } else {
            Pin::setOrUnsetDigit();
            Disp::drawPin();
        }
    }
}