#include <Arduino.h>
#include "interuptive.h"
#include "display.h"
#include "seed.h"

unsigned long Interaptive::lastButtonTime = 0;
bool Interaptive::_previousClicked = false;
bool Interaptive::_nextClicked = false;

Interaptive::Interaptive() = default;

void Interaptive::begin(uint8_t previousButton, uint8_t nextButton) {
    attachInterrupt(previousButton, Interaptive::clickPrevious(), RISING);
    attachInterrupt(nextButton, Interaptive::clickNext(), RISING);
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
    _nextClicked = false;
    return was;
}
