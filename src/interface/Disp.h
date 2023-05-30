#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#endif //WALLET_POC_DISPLAY_H

class Disp {
public:
    static unsigned long lastTextBlinked;
    static void begin();
    static void setText(const std::string& text);
    static void blinkTextWithSign(const std::string &text);
    static void drawPin();
    static void drawNo();
    static void drawYes();
    static void drawOneBox(const std::string &text, uint8_t width, uint8_t cursorPos);
    static void clearText();
    static void clearMenu();
    //static void clear();
private:
    static bool blink;

    static void animateText(const std::string &text1, const std::string &text2);
};