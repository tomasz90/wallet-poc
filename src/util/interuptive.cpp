#include <Arduino.h>
#include "interuptive.h"
#include "display.h"
#include "seed.h"

int Interaptive::wordIndex = -1;
unsigned long Interaptive::lastButtonTime = 0;

void Interaptive::innerNextWord() {
    unsigned long buttonTime = millis();
    if (buttonTime - lastButtonTime > 700) {
        lastButtonTime = buttonTime;
        wordIndex++;
        std::string humanIndex = std::to_string(wordIndex + 1).append(". ");
        Display::_word = Seed::passphrase.getWordAt(wordIndex);
        Display::_word.insert(0, humanIndex);
    }
}

void Interaptive::begin(uint8_t previousButton, uint8_t nextButton) {
    attachInterrupt(nextButton, Interaptive::nextWord(), RISING);
}

void (*Interaptive::nextWord())() {
    return innerNextWord;
}

Interaptive::Interaptive() = default;
