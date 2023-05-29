#include <cstdint>
#include "Led.h"
#include "ButtonsHandler.h"

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

class Menu {

public:
    static bool previousCalled;
    static bool nextCalled;
    static bool bothCalled;

    Menu();
    static void begin(Led *led, ButtonsHandler &buttonHandler);
    static void run();

private:

    static Led* led;
    static bool isPreviousCalled();
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
    static void enterPin(int position);
    static void onPrevious();
    static void onNext();
    static void onBoth();
    static bool isNextForPin();
    static bool isPreviousForPin();
};

#endif //WALLET_POC_MENU_H
