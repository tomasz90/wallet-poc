#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#endif //WALLET_POC_DISPLAY_H

class Disp {
public:
    static bool firstTime;
    static void begin();
    static void setText(const std::string& text);
    static void blinkTextWithSign(const std::string &text);
    static void drawPin();
    static void drawNo();
    static void drawYes();
    static void clear();
    static void clearText();
    static void clearMenu();
private:
    static bool blink;
    static unsigned long lastTextBlinked;

    static void animateText(const std::string &text1, const std::string &text2);
};