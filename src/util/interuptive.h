#include <esp_attr.h>
#include "button.h"

#ifndef WALLET_POC_INTERUPTIVE_H
#define WALLET_POC_INTERUPTIVE_H

#endif //WALLET_POC_INTERUPTIVE_H

class Interaptive {
public:
    static int wordIndex;
    static unsigned long previousButtonTime;
    static unsigned long nextButtonTime;

    static void (*clickPrevious())();
    static void (*clickNext())();

    static bool previousClicked();
    static bool nextClicked();
    static void begin(uint8_t previousButton, uint8_t nextButton, uint8_t led);

    static bool bothClicked();

private:
    static Button previous;
    static Button next;
    Interaptive();
    static void flashLed();
    static void setupLed(uint8_t _led);
};
