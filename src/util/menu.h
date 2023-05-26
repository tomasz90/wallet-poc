#include <cstdint>

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

#endif //WALLET_POC_MENU_H

class Menu {
public:
    static void begin();
    static void run();
private:
    static unsigned long lastUpdated;

    Menu();

    static bool next();

    static void s0();

    static void s2();

    static void s3();

    static bool previous();

    static void s5();

    static bool both();

    static void s1();

    static void s4();
};
