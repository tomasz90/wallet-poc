#include <Arduino.h>
#include "listener.h"
#include "util/display.h"
#include "util/seed.h"

const int ledChannel = 0;    // LEDC channel (0-15)
Button* Listener::previous;
Button* Listener::next;

void Listener::begin(uint8_t previousButton, uint8_t nextButton, uint8_t _led) {
    pinMode(previousButton, INPUT_PULLUP);
    pinMode(nextButton, INPUT_PULLUP);
    setupLed(_led);
    previous = new Button("PREVIOUS");
    next = new Button("NEXT");
    attachInterrupt(previousButton, Listener::clickPrevious(), RISING);
    attachInterrupt(nextButton, Listener::clickNext(), RISING);
}

void Listener::setupLed(uint8_t led) {
    pinMode(led, OUTPUT);
    ledcSetup(ledChannel, 5000, 8);  // Set PWM frequency and resolution
    ledcAttachPin(led, ledChannel);
}

void (*Listener::clickPrevious())() {
    return [] { setPendingIfItIsNot(previous); };
}

void (*Listener::clickNext())() {
    return [] { setPendingIfItIsNot(next); };
}

void Listener::setPendingIfItIsNot(Button *&button) {
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
    delay(20);
    ledcWrite(ledChannel, 0);
}
