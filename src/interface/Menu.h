#include <cstdint>
#include "util/Led.h"
#include "ButtonsHandler.h"
#include "util/Nav.h"
#include "Disp.h"

#ifndef WALLET_POC_MENU_H
#define WALLET_POC_MENU_H

class Menu {

public:
    Nav *nav;
    Disp *disp;
    Menu(Nav *_nav, Disp *_disp, SeedGenerator *_seedGenerator);
    void run();
    void doOnce(const std::function<void()>& _doOnce);
private:
    SeedGenerator *seedGenerator;

    void s0();
    void s1_0();
    void s1_1();
    void s2();
    void s3();
    void s4_0();
    void s4_1();
    void s5();
    void s6_0();
    void s6_1();
    void s6_2();
    void s7();
    void s8_0();
    void s8_1();
    void s8_2();
    void s9_1();
    void s9_2();
    void s9_3();
    void s9_0();
    void s9_4();
};

#endif //WALLET_POC_MENU_H
