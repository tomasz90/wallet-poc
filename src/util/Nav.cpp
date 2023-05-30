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

bool Nav::isPrevious() {
    bool called = previousCalled;
    resetAll(called);
    return called;
}

bool Nav::isNext() {
    bool called = nextCalled;
    resetAll(called);
    return called;
}

bool Nav::isBoth() {
    bool called = bothCalled;
    resetAll(called);
    return called;
}

void Nav::resetAll(bool doReset) {
    if (doReset) {
        Nav::previousCalled = false;
        Nav::nextCalled = false;
        Nav::bothCalled = false;
    }
}

void Nav::enterPin() {
    if (isNext()) {
        Pin::incrementCurrentDigit();
        Disp::drawPin();
    } else if (isPrevious()) {
        Pin::decrementCurrentDigit();
        Disp::drawPin();
    } else if (isBoth()) {
        if(!Pin::isArrow() && Pin::currentIndex == 3) {
            Pin::setDigit();
            Pin::savePin();
            nextPinBothCalled = true;
        } else if(Pin::isArrow() && Pin::currentIndex == 0) {
            previousPinBothCalled = true;
        } else {
            Pin::setDigit();
            Disp::drawPin();
        }
    }
}

bool Nav::isNextPin() {
    if (nextPinBothCalled) {
        nextPinBothCalled = false;
        return true;
    }
    return false;
}

bool Nav::isPreviousPin() {
    if (previousPinBothCalled) {
        previousPinBothCalled = false;
        return true;
    }
    return false;
}