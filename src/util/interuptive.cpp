#include <Arduino.h>
#include "interuptive.h"
#include "display.h"
#include "seed.h"

uint8_t led;
const int ledChannel = 0;    // LEDC channel (0-15)
const int pwmResolution = 8; // PWM resolution (8-bit: 0-255)

unsigned long Interaptive::lastButtonTime = 0;
bool Interaptive::_previousClicked = false;
bool Interaptive::_nextClicked = false;

Interaptive::Interaptive() = default;

void Interaptive::begin(uint8_t previousButton, uint8_t nextButton, uint8_t _led) {
    pinMode(previousButton, INPUT);
    pinMode(nextButton, INPUT);
    setupLed(_led);
    attachInterrupt(previousButton, Interaptive::clickPrevious(), RISING);
    attachInterrupt(nextButton, Interaptive::clickNext(), RISING);
}

void Interaptive::setupLed(uint8_t _led) {
    led = _led;
    pinMode(led, OUTPUT);
    ledcSetup(ledChannel, 5000, pwmResolution);  // Set PWM frequency and resolution
    ledcAttachPin(led, ledChannel);
}

void (*Interaptive::clickPrevious())() {
    return [] { _previousClicked = isActive(); };
}

void (*Interaptive::clickNext())() {
    return [] { _nextClicked = isActive(); };
}

bool Interaptive::isActive() {
    unsigned long buttonTime = millis();

    bool isActive = buttonTime - lastButtonTime > 300;
    if (isActive) {
        lastButtonTime = buttonTime;
    }
    return isActive;
}

bool Interaptive::previousClicked() {
    bool was = _previousClicked;
    _previousClicked = false;
    return was;
}

bool Interaptive::nextClicked() {
    bool was = _nextClicked;
    flashLed(was);
    _nextClicked = false;
    return was;
}

void Interaptive::flashLed(bool flash) {
    if (flash) {
        ledcWrite(ledChannel, 2);
        delay(100);
        ledcWrite(ledChannel, 0);
    }
}
