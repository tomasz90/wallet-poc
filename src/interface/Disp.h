#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#endif //WALLET_POC_DISPLAY_H

#define SCREEN_TEXT_MENU_BORDER_POSITION 40

using std::string;

class Disp {
public:
    static unsigned long lastTextBlinked;
    static void begin();
    static void setText(const string &text, uint8_t toLine);
    static void setTextAtCenter(const string &text, uint8_t y);
    static void blinkTextWithSign(const string &text, uint8_t toLine);
    static void blinkTextWarningAtCenter(const string &text);
    static void drawPin(const string &pin);
    static void drawTwoBoxes(const string &text1, const string &text2, bool rightHighlighted);
    static void drawOnlyLeftBox(const string &text);
    static void drawOnlyRightBox(const string &text);
    static void drawOneBox(const string &text, uint8_t width);
    static void clearText(uint8_t toLine);
    static void clearTextCenter();
    static void clearMenu();
    static void blinkTextWithSign(const string &text);
    static void disp();
    static void drawTransaction(const string &chainId, const string &to, const string &value);

private:
    static bool blink;
    static void setCursorRelativeToCenter(const string &text, uint8_t textCenter, uint8_t y);
    static void animateText(const string &text1, const string &text2, uint8_t toLine);
    static void drawLeftBox(const string &text, bool highlighted);
    static void drawRightBox(const string &text, bool highlighted);
};