#include <cstdint>

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

#endif //WALLET_POC_MENU_H

class Menu {
public:
    static void begin();
    static void run();

    static void anyTransition();

private:

    Menu();

    static bool previous();

    static bool next();

    static bool both();

    static void s0();

    static void s1_0();

    static void s1_1();

    static void s1_2();

    static void s1_3();

    static void s2_0();

    static void s2_1();

    static void s3();

    static bool noHandle();

    static void enterPin(int position);

};
