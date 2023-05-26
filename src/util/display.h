#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#endif //WALLET_POC_DISPLAY_H

class Display {
public:
    static void begin(Adafruit_SSD1306 &_display);
    static void setText(const std::string& text);
    static void animateText(const std::string &text1, const std::string &text2);

    static void clearText();

    static void blinkTextWithSign(const std::string &text);

private:
    static Adafruit_SSD1306 display;
    static bool blink;
    static unsigned long lastChange;

};