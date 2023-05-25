#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#endif //WALLET_POC_DISPLAY_H

class Display {
public:
    static std::string _word;

    static void begin();

    static void setText(std::string text);

    static void animateText();

private:
    static Adafruit_SSD1306 display;
    static unsigned long previousMillis;
    static bool blink;

    Display();
};