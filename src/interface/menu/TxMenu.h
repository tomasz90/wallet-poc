#ifndef TXMENU_H
#define TXMENU_H

#include "AbstractMenu.h"

class TxMenu : public AbstractMenu {
public:
    Repository *repository;

    TxMenu(CustomMachine *_machine, Nav *_nav, Disp *_disp, Repository *_repository)
            : AbstractMenu(_machine, _nav, _disp) {
        this->repository = _repository;
    };

    void s0() {
        doOnce([this]() { disp->clearMenu(); });
        disp->blinkTextWithSign("Waiting for bluetooth connection...");
    }

    void s1() {
        doOnce([this]() {
            disp->clearMenu();
            nav->sendAddress();
        });
        disp->blinkTextWithSign("Device connected!   Listening for txs..");
        nav->listenTx();
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
