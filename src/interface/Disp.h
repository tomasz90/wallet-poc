#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#define SCREEN_TEXT_MENU_BORDER_POSITION 40

using std::string;

class Disp {
public:
    unsigned long lastTextBlinked;
    Disp();
    void setText(const string &text, uint8_t toLine);
    void setTextAtCenter(const string &text, uint8_t y);
    void blinkTextWithSign(const string &text, uint8_t toLine);
    void blinkTextWarningAtCenter(const string &text);
    void drawPin(const string &pin);
    void drawTwoBoxes(const string &text1, const string &text2, bool rightHighlighted);
    void drawOnlyLeftBox(const string &text);
    void drawOnlyRightBox(const string &text);
    void drawOneBox(const string &text, uint8_t width);
    void clearText(uint8_t toLine);
    void clearTextCenter();
    void clearMenu();
    void blinkTextWithSign(const string &text);
    void disp();
    void drawTransaction(const string &chainId, const string &to, const string &value);

private:
    bool blink;
    void setCursorRelativeToCenter(const string &text, uint8_t textCenter, uint8_t y);
    void animateText(const string &text1, const string &text2, uint8_t toLine);
    void drawLeftBox(const string &text, bool highlighted);
    void drawRightBox(const string &text, bool highlighted);
};

#endif //WALLET_POC_DISPLAY_H