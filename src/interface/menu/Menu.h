#include <cstdint>
#include "interface/Disp.h"
#include "io/Led.h"
#include "ButtonsHandler.h"
#include "interface/Nav.h"
#include "customStateMachine/CustomMachine.h"
#include "interface/menu/UnlockMenu.h"
#include "interface/menu/SetPinMenu.h"
#include "interface/menu/SetMnemonicMenu.h"
#include "interface/menu/TxMenu.h"
#include "util/Battery.h"

#ifndef MENU_H
#define MENU_H

CustomMachine machine = CustomMachine();

using std::string;

class Menu {
public:
    Menu(Disp* disp, SeedViewer* seedViewer, SeedVerifier* seedVerifier, Repository* repository,
         Pin* pin, Led* led, ButtonsHandler &buttonHandler, Battery* battery) {

        auto nav = new Nav(disp, seedViewer, seedVerifier, repository, pin, led, buttonHandler);

        auto unlock = new UnlockMenu(&machine, nav, disp, pin, repository, battery);
        auto setPin = new SetPinMenu(&machine, nav, disp, pin);
        auto setMne = new SetMnemonicMenu(&machine, nav, disp, pin, repository, seedViewer, seedVerifier);
        auto txMenu = new TxMenu(&machine, nav, disp, repository);

        // STATES
        CustomState* unlockS0 = machine.addState([unlock]() { unlock->s0(); });
        CustomState* unlockS1 = machine.addState([unlock]() { unlock->s1(); });
        CustomState* unlockS2 = machine.addState([unlock]() { unlock->s2(); });
        CustomState* unlockS3 = machine.addState([unlock]() { unlock->s3(); });

        CustomState* setPinS0 = machine.addState([setPin]() { setPin->s0(); });
        CustomState* setPinS1 = machine.addState([setPin]() { setPin->s1(); });
        CustomState* setPinS2 = machine.addState([setPin]() { setPin->s2(); });
        CustomState* setPinS3 = machine.addState([setPin]() { setPin->s3(); });
        CustomState* setPinS4 = machine.addState([setPin]() { setPin->s4(); });
        CustomState* setPinS5 = machine.addState([setPin]() { setPin->s5(); });

        CustomState* setMneS0 = machine.addState([setMne]() { setMne->s0(); });
        CustomState* setMneS1 = machine.addState([setMne]() { setMne->s1(); });
        CustomState* setMneS2 = machine.addState([setMne]() { setMne->s2(); });
        CustomState* setMneS3 = machine.addState([setMne]() { setMne->s3(); });
        CustomState* setMneS4 = machine.addState([setMne]() { setMne->s4(); });
        CustomState* setMneS5 = machine.addState([setMne]() { setMne->s5(); });
        CustomState* setMneS6 = machine.addState([setMne]() { setMne->s6(); });
        CustomState* setMneS7 = machine.addState([setMne]() { setMne->s7(); });

        CustomState* txMenuS0 = machine.addState([txMenu]() { txMenu->s0(); });
        CustomState* txMenuS1 = machine.addState([txMenu]() { txMenu->s1(); });
        CustomState* txMenuS2 = machine.addState([txMenu]() { txMenu->s2(); });
        CustomState* txMenuS3 = machine.addState([txMenu]() { txMenu->s3(); });
        CustomState* txMenuS4 = machine.addState([txMenu]() { txMenu->s4(); });

        unlockS0->addTransition(unlockS1, nav->bothCalledAndInit);
        unlockS0->addTransition(setPinS0, nav->bothCalledAndNotInit);
        unlockS1->addTransition(unlockS2, nav->failureCalled);
        unlockS1->addTransition(unlockS3, nav->resetDeviceCalled);
        unlockS1->addTransition(txMenuS0, nav->successCalled);
        unlockS2->addTransition(unlockS1, nav->bothCalled);
        unlockS3->addTransition(unlockS0, nav->bothCalled);

        setPinS0->addTransition(setPinS1, nav->nextCalled);
        setPinS1->addTransition(setPinS2, nav->bothCalled);
        setPinS1->addTransition(setPinS0, nav->previousCalled);
        setPinS2->addTransition(setPinS3, nav->successCalled);
        setPinS3->addTransition(setPinS4, nav->successCalled);
        setPinS3->addTransition(setPinS5, nav->failureCalled);
        setPinS4->addTransition(setMneS0, nav->bothCalled);
        setPinS5->addTransition(setPinS2, nav->bothCalled);

        setMneS0->addTransition(setMneS1, nav->bothCalled);
        setMneS1->addTransition(setMneS2, nav->bothCalledWrapped);
        setMneS2->addTransition(setMneS3, nav->previousCalled);
        setMneS2->addTransition(setMneS4, nav->successCalled);
        setMneS3->addTransition(setMneS2, nav->nextCalled);
        setMneS3->addTransition(setMneS1, nav->beginCalled);
        setMneS4->addTransition(setMneS5, nav->bothCalledAndBtConnected);
        setMneS5->addTransition(setMneS6, nav->bothCalledWrapped);
        setMneS6->addTransition(setMneS7, nav->previousCalled);
        setMneS6->addTransition(txMenuS0, nav->successCalled);
        setMneS7->addTransition(setMneS6, nav->nextCalled);
        setMneS7->addTransition(setMneS5, nav->beginCalled);

        txMenuS0->addTransition(txMenuS1, nav->btConnectedCalled);
        txMenuS1->addTransition(txMenuS2, nav->receivedTxCalled);
        txMenuS1->addTransition(txMenuS0, nav->btDisconnectedCalled);
        txMenuS2->addTransition(txMenuS3, nav->nextCalled);
        txMenuS2->addTransition(txMenuS1, nav->bothCalled);
        txMenuS2->addTransition(txMenuS0, nav->btDisconnectedCalled);
        txMenuS3->addTransition(txMenuS4, nav->bothCalled);
        txMenuS3->addTransition(txMenuS0, nav->btDisconnectedCalled);
        txMenuS3->addTransition(txMenuS2, nav->previousCalled);
        txMenuS4->addTransition(txMenuS1, nav->bothCalled);
    }

    void run() {
        machine.run();
    }
};

#endif //MENU_H
