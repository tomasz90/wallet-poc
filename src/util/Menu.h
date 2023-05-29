#include <cstdint>
#include "Led.h"
#include "ButtonsHandler.h"

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

class Menu {

public:
    Menu();
    static void begin();
    static void run();

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
