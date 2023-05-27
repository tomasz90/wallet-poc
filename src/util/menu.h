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

    static void s1_0();

    static void s1_1();

    static void s1_2();

    static void s1_3();

    static void s1_4();

    static void s2_0();

    static void s2_1();

    static void s3();

    static bool pinNext();

    static bool pinPrevious();

    static void enterPin(const int &position);
};
