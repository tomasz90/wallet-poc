#include <Arduino.h>
#include "listener.h"
#include "util/display.h"
#include "util/seed.h"

const int ledChannel = 0;    // LEDC channel (0-15)
unsigned long lastPreviousButtonTime;
unsigned long lastNextButtonTime;
Button* Listener::previous;
Button* Listener::next;

void Listener::begin(uint8_t previousButton, uint8_t nextButton, uint8_t _led) {
    pinMode(previousButton, INPUT_PULLDOWN);
    pinMode(nextButton, INPUT_PULLDOWN);
    setupLed(_led);
    previous = new Button("PREVIOUS");
    next = new Button("NEXT");
    attachInterrupt(previousButton, Listener::clickPrevious(), HIGH);
    attachInterrupt(nextButton, Listener::clickNext(), HIGH);
}

void Listener::setupLed(uint8_t led) {
    pinMode(led, OUTPUT);
    ledcSetup(ledChannel, 5000, 8);  // Set PWM frequency and resolution
    ledcAttachPin(led, ledChannel);
}

void (*Listener::clickPrevious())() {
    return [] { setPendingIfItIsNot(previous, lastPreviousButtonTime); };
}

void (*Listener::clickNext())() {
    return [] { setPendingIfItIsNot(next, lastNextButtonTime); };
}

void Listener::setPendingIfItIsNot(Button *&button, unsigned long &lastButtonTime) {
    unsigned long buttonTime = millis();
    if (buttonTime - lastButtonTime < 300) {
        return;
    }
    lastButtonTime = buttonTime;
    if (!button->isPendingClick()) {
        button->setPending();
    }
}

bool Listener::isPreviousClicked() {
    return clicked(previous);
}

bool Listener::isNextClicked() {
    return clicked(next);
}

bool Listener::clicked(Button *&button) {
    bool canBeClicked = button->canBeClicked();
    if (canBeClicked) {
        Serial.println(button->getName().c_str());
        button->setClicked();
        flashLed();
    }
    return canBeClicked;
}

bool Listener::isBothClicked() {
    bool canBeClicked = previous->isPendingClick() && next->isPendingClick();
    if (canBeClicked) {
        Serial.println("BOTH");
        previous->setClicked();
        next->setClicked();
        flashLed();
    }
    return canBeClicked;
}

void Listener::flashLed() {
    ledcWrite(ledChannel, 2);
    delay(10);
    ledcWrite(ledChannel, 0);
}
