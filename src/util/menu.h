#include <cstdint>

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

class Menu {
public:
    static bool previousCalled;
    static bool nextCalled;
    static bool bothCalled;

    static void begin();
    static void run();
    static void anyTransition();
    static bool isPreviousCalled();

private:

    Menu();

    static bool isNextCalled();
    static bool isBothCalled();
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

#endif //WALLET_POC_MENU_H
