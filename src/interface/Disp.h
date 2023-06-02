#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_DISPLAY_H
#define WALLET_POC_DISPLAY_H

#endif //WALLET_POC_DISPLAY_H

class Disp {
public:
    static unsigned long lastTextBlinked;
    static void begin();
    static void setText(const std::string &text);
    static void blinkTextWithSign(const std::string &text);
    static void drawPin();
    static void drawTwoBoxes(const std::string &text1, const std::string &text2, bool leftHighlighted);
    static void drawOnlyLeftBox(const std::string &text);
    static void drawOnlyRightBox(const std::string &text);
    static void drawOneBox(const std::string &text, uint8_t width);
    static void clearText();
    static void clearMenu();
private:

    static bool blink;
    static void setCursorRelativeToCenter(const std::string &text, uint8_t textCenter);
    static void animateText(const std::string &text1, const std::string &text2);
    static void drawLeftBox(const std::string &text, bool highlighted);
    static void drawRightBox(const std::string &text, bool highlighted);
};