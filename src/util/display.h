#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#endif //WALLET_POC_DISPLAY_H

class Disp {
public:
    static std::string pin;
    static int pinNumber;
    static int lastPinNumber;
    static void begin(Adafruit_SSD1306 &_display);
    static void setText(const std::string& text);
    static void blinkTextWithSign(const std::string &text);
    static void drawPin();
    static void drawNo();
    static void drawYes();
    static void clear();
    static void incrementPinNumber();
    static void decrementPinNumber();
    static void randomPinNumber();

    static std::string getPinChar();

    static std::string getLastPinChar();

private:
    static Adafruit_SSD1306 display;
    static bool blink;
    static unsigned long lastTextBlinked;
    static void animateText(const std::string &text1, const std::string &text2);
    static void clearText();

};