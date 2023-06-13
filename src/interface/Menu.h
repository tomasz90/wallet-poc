#include <cstdint>
#include "io/Led.h"
#include "ButtonsHandler.h"
#include "Nav.h"
#include "Disp.h"
#include "seed/SeedViewer.h"

#ifndef MENU_H
#define MENU_H

class Menu {

public:

    Menu(Nav *_nav, Disp *_disp, SeedViewer *_seedViewer, SeedVerifier *_seedVerifier, Repository *_repository,
         Pin *_pin);
    void run();
    void doOnce(const std::function<void()>& _doOnce);
private:
    Disp *disp;
    Nav *nav;
    SeedViewer *seedViewer;
    SeedVerifier *seedVerifier;
    Pin *pin;
    Repository *repository;

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

#endif //MENU_H
