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

    static bool previous();

    static bool next();

    static bool both();

    static void s0();

    static void s1();

    static void s2_0();

    static void s2_1();

    static void s3();
};
