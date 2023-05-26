#include <Arduino.h>
#include "interuptive.h"
#include "display.h"
#include "seed.h"

uint8_t led;
const int ledChannel = 0;    // LEDC channel (0-15)
const int pwmResolution = 8; // PWM resolution (8-bit: 0-255)
Button Interaptive::previous;
Button Interaptive::next;
unsigned long lastPreviousButtonTime;
unsigned long lastNextButtonTime;


Interaptive::Interaptive() = default;

void Interaptive::begin(uint8_t previousButton, uint8_t nextButton, uint8_t _led) {
    pinMode(previousButton, INPUT_PULLDOWN);
    pinMode(nextButton, INPUT_PULLDOWN);
    setupLed(_led);
    previous = Button();
    next = Button();
    attachInterrupt(previousButton, Interaptive::clickPrevious(), HIGH);
    attachInterrupt(nextButton, Interaptive::clickNext(), HIGH);
}

void Interaptive::setupLed(uint8_t _led) {
    led = _led;
    pinMode(led, OUTPUT);
    ledcSetup(ledChannel, 5000, pwmResolution);  // Set PWM frequency and resolution
    ledcAttachPin(led, ledChannel);
}

void (*Interaptive::clickPrevious())() {
    return [] { setPendingIfItIsNot(previous, lastPreviousButtonTime); };
}

void (*Interaptive::clickNext())() {
    return [] { setPendingIfItIsNot(next, lastNextButtonTime); };
}

void Interaptive::setPendingIfItIsNot(Button &button, unsigned long &lastButtonTime) {
    unsigned long buttonTime = millis();
    if (buttonTime - lastButtonTime < 200) {
        return;
    }
    lastButtonTime = buttonTime;
    if (!button.isPendingClick()) {
        button.setPending();
    }
}

bool Interaptive::previousClicked() {
    bool canBeClicked = previous.canBeClicked();
    if (canBeClicked) {
        Serial.println("PREVIOUS");
        previous.setClicked();
        flashLed();
    }
    return canBeClicked;
}

bool Interaptive::nextClicked() {
    bool canBeClicked = next.canBeClicked();
    if (canBeClicked) {
        Serial.println("NEXT");
        next.setClicked();
        flashLed();
    }
    return canBeClicked;
}

bool Interaptive::bothClicked() {
    bool pendings = previous.isPendingClick() && next.isPendingClick();
    if (pendings) {
        Serial.println("BOTH");
        previous.setClicked();
        next.setClicked();
        flashLed();
    }
    return pendings;
}

void Interaptive::flashLed() {
    ledcWrite(ledChannel, 2);
    delay(20);
    ledcWrite(ledChannel, 0);
}
