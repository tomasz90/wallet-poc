#ifndef TXMENU_H
#define TXMENU_H

#include "AbstractMenu.h"

class TxMenu : public AbstractMenu {
public:
    Repository* repository;

    TxMenu(CustomMachine* machine, Nav* nav, Disp* disp, Repository* repository)
            : AbstractMenu(machine, nav, disp), repository(repository) {};

    void s0() {
        doOnce([this]() {
            disp->clearMenu();
            nav->startAdvertising();
        });
        disp->blinkTextWithSign("Waiting for bluetooth connection...");
    }

    void s1() {
        doOnce([this]() {
            disp->clearMenu();
        });
        disp->blinkTextWithSign("Device connected!   Listening for txs..");
        nav->listenTx();
        if (nav->deviceConnected && millis() - nav->connectionTime > 2200 && nav->executeOnce) {
            nav->executeOnce = false;
            nav->sendAddress();
        }
    }

    void s2() {
        doOnce([this]() {
            //todo: possible flickering, keep in mind
            disp->clearText(SCREEN_TEXT_MENU_BORDER_POSITION);

            string chainId = repository->tx->formatChainId();
            string address = repository->tx->formatAddress();
            string value = repository->tx->formatEthValue();

            disp->drawTransaction(chainId, address, value);
            disp->drawTwoBoxes("DECLINE", "ACCEPT", false);
        });
    }

    void s3() {
        doOnce([this]() {
            disp->drawTwoBoxes("DECLINE", "ACCEPT", true);
        });
    }

    void s4() {
        doOnce([this]() {
            nav->signTx();
            disp->drawOnlyLeftBox("BACK");
        });

        disp->blinkTextWithSign("Tx sent!");
    }
};

#endif //TXMENU_H
