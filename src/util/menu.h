#include <cstdint>

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

#endif //WALLET_POC_MENU_H

class Menu {
public:
    static void begin(uint8_t led);
    static void run();
private:
    static uint8_t led;

    Menu();

    static bool next();

    static void welcome();

    static void newOrOld();

    static void generateSeed();

    static void flashLed(bool flash);
};
