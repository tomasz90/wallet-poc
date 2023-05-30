#include "Nav.h"
#include "Pin.h"
#include "Led.h"
#include "interface/Disp.h"
#include "ButtonsHandler.h"

bool Nav::previousCalled = false;
bool Nav::nextCalled = false;
bool Nav::bothCalled = false;

Led *Nav::led = nullptr;

void Nav::begin(Led *_led, ButtonsHandler &buttonHandler) {
    led = _led;
    buttonHandler.setCallbacks(onPrevious, onNext, onBoth);
}

void Nav::onPrevious() {
    led->flash();
    Nav::previousCalled = true;
}
void Nav::onNext() {
    led->flash();
    Nav::nextCalled = true;
}
void Nav::onBoth() {
    led->flash();
    Nav::bothCalled = true;
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
        Pin::incrementCurrentNumber();
        Disp::drawPin();
    } else if (isPrevious()) {
        Pin::decrementCurrentNumber();
        Disp::drawPin();
    } else if(isBoth()) {
        if(Pin::isArrow()) {
            Pin::unsetOneDigit();
        } else {
            Pin::setOneDigit();
        }
        Disp::drawPin();
    }
}

bool Nav::isNextPin() {
    if (bothCalled && !Pin::isArrow() && Pin::currentIndex == 3) {
        bothCalled = false;
        return true;
    }
    return false;
}

bool Nav::isPreviousPin() {
    if (bothCalled && Pin::isArrow() && Pin::currentIndex == 0) {
        bothCalled = false;
        return true;
    }
    return false;
}