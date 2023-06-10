#include <cstdint>
#include "util/Led.h"
#include "ButtonsHandler.h"
#include "util/Nav.h"

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

class Menu {

public:
    static bool firstTime;
    static Nav *nav;
    Menu();
    static void begin(Nav *nav);
    static void run();
    static void doOnce(void (*_doOnce)());
private:
    static void s0();
    static void s1_0();
    static void s1_1();
    static void s2();
    static void s3();
    static void s4_0();
    static void s4_1();
    static void s5();
    static void s6_0();
    static void s6_1();
    static void s6_2();
    static void s7();
    static void s8_0();
    static void s8_1();
    static void s8_2();
    static void s9_1();
    static void s9_2();

    static void s9_3();

    static void s9_0();

    static void s9_4();
};

#endif //WALLET_POC_MENU_H
