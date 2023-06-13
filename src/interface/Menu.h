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
private:

};

#endif //MENU_H
