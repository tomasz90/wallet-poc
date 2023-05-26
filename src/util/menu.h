#include <cstdint>

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

#endif //WALLET_POC_MENU_H

class Menu {
public:
    static void begin();
    static void run();
private:
    Menu();

    static bool next();

    static void welcome();

    static void newOrOld();

    static void generateSeed();

    static bool previous();

    static void confirm();

    static bool both();

    static void setPin();

    static void enterSeed();
};
