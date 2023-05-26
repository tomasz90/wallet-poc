#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#endif //WALLET_POC_DISPLAY_H

class Display {
public:
    static void begin();
    static void setText(const std::string& text);
    static void animateText(const std::string &_text);
private:
    static Adafruit_SSD1306 display;
    static bool blink;
    static unsigned long previousMillis;

    Display();

    static void drawNo();

    static void drawYes();
};