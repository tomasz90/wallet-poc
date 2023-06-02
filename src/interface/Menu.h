#include <cstdint>
#include "util/Led.h"
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
    static void s2();
    static void s3();
    static void s4_0();
    static void s4_1();
    static void s5();
    static void s6_0();
    static void s6_1();
    static void s6_2();
    static void s7();
    static void s8();
    static void readStringFromSerial();
};

#endif //WALLET_POC_MENU_H
