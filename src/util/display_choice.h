#include "Adafruit_SSD1306.h"

#ifndef WALLET_POC_CHOOSE_MENU_H
#define WALLET_POC_CHOOSE_MENU_H

#endif //WALLET_POC_CHOOSE_MENU_H

class DisplayChoice {
public:
    DisplayChoice();
    static void begin(Adafruit_SSD1306 &_display);
    static void drawNo();
    static void drawYes();
private:
    static Adafruit_SSD1306 display;
    static void clearBoxes();
};
