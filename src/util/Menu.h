#include <cstdint>
#include "Led.h"
#include "ButtonsHandler.h"

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

class Menu {

public:
    static bool firstTime;
    Menu();
    static void begin();
    static void run();

    static void doOnce(void (*_doOnce)());
private:

    static void s0();
    static void s1_0();
    static void s1_1();
    static void s1_2();
    static void s1_3();
    static void s2_0();
    static void s2_1();
    static void s3();
};

#endif //WALLET_POC_MENU_H
