#include "Menu.h"
#include "customStateMachine/CustomMachine.h"
#include "ButtonsHandler.h"
#include "Nav.h"
#include "seed/SeedVerifier.h"
#include "io/Bluetooth.h"
#include "interface/menu/UnlockMenu.h"
#include "interface/menu/SetPinMenu.h"
#include "interface/menu/SetMnemonicMenu.h"
#include "interface/menu/TxMenu.h"

CustomMachine machine = CustomMachine();

using std::string;

Menu::Menu(Nav *nav, Disp *disp, SeedViewer *seedViewer, SeedVerifier *seedVerifier, Repository *repository,
           Pin *pin) {

    auto unlock = new UnlockMenu(&machine, nav, disp, pin, repository);
    auto setPin = new SetPinMenu(&machine, nav, disp, pin);
    auto setMnemonic = new SetMnemonicMenu(&machine, nav, disp, pin, repository, seedViewer, seedVerifier);
    auto txMenu = new TxMenu(&machine, nav, disp, repository);

    // STATES
    CustomState *S0 = machine.addState([unlock]() { unlock->s0(); });
    CustomState *S1_0 = machine.addState([setPin]() { setPin->s1_0(); });
    CustomState *S1_0_ = machine.addState([unlock]() { unlock->s1_0_(); });
    CustomState *S1_1_ = machine.addState([unlock]() { unlock->s1_1_(); });
    CustomState *S1_2_ = machine.addState([unlock]() { unlock->s1_2_(); });
    CustomState *S1_1 = machine.addState([setPin]() { setPin->s1_1(); });
    CustomState *S2 = machine.addState([setPin]() { setPin->s2(); });
    CustomState *S3 = machine.addState([setPin]() { setPin->s3(); });
    CustomState *S4_0 = machine.addState([setPin]() { setPin->s4_0(); });
    CustomState *S4_1 = machine.addState([setPin]() { setPin->s4_1(); });
    CustomState *S5 = machine.addState([setMnemonic]() { setMnemonic->s5(); });
    CustomState *S6_0 = machine.addState([setMnemonic]() { setMnemonic->s6_0(); });
    CustomState *S6_1 = machine.addState([setMnemonic]() { setMnemonic->s6_1(); });
    CustomState *S6_2 = machine.addState([setMnemonic]() { setMnemonic->s6_2(); });
    CustomState *S7 = machine.addState([setMnemonic]() { setMnemonic->s7(); });
    CustomState *S8_0 = machine.addState([setMnemonic]() { setMnemonic->s8_0(); });
    CustomState *S8_1 = machine.addState([setMnemonic]() { setMnemonic->s8_1(); });
    CustomState *S8_2 = machine.addState([setMnemonic]() { setMnemonic->s8_2(); });
    CustomState *S9_0 = machine.addState([txMenu]() { txMenu->s9_0(); });
    CustomState *S9_1 = machine.addState([txMenu]() { txMenu->s9_1(); });
    CustomState *S9_2 = machine.addState([txMenu]() { txMenu->s9_2(); });
    CustomState *S9_3 = machine.addState([txMenu]() { txMenu->s9_3(); });
    CustomState *S9_4 = machine.addState([txMenu]() { txMenu->s9_4(); });

    S0->addTransition(S1_0_, nav->bothCalledAndInit);
    S0->addTransition(S1_0, nav->bothCalledAndNotInit);
    S1_0_->addTransition(S1_1_, nav->pinMismatchCalled);
    S1_0_->addTransition(S1_2_, nav->resetDeviceCalled);
    S1_0_->addTransition(S9_0, nav->confirmPinCalled);
    S1_1_->addTransition(S1_0_, nav->bothCalled);
    S1_2_->addTransition(S0, nav->bothCalled);
    S1_0->addTransition(S1_1, nav->nextCalled);
    S1_1->addTransition(S2, nav->bothCalled);
    S1_1->addTransition(S1_0, nav->previousCalled);
    S2->addTransition(S1_0, nav->dropPinCalled);
    S2->addTransition(S3, nav->confirmPinCalled);
    S3->addTransition(S2, nav->dropPinCalled);
    S3->addTransition(S4_0, nav->confirmPinCalled);
    S3->addTransition(S4_1, nav->pinMismatchCalled);
    S4_0->addTransition(S5, nav->bothCalled);
    S4_1->addTransition(S2, nav->bothCalled);
    S5->addTransition(S6_0, nav->bothCalled);
    S6_0->addTransition(S6_1, nav->bothCalledWrapped);
    S6_1->addTransition(S6_2, nav->previousCalled);
    S6_1->addTransition(S7, nav->confirmSeedScreenCalled);
    S6_2->addTransition(S6_1, nav->nextCalled);
    S6_2->addTransition(S6_0, nav->firstSeedScreenCalled);
    S7->addTransition(S8_0, nav->bothCalledAndBtConnected);
    S8_0->addTransition(S8_1, nav->bothCalledWrapped); // this is set internally after checking bothCalled
    S8_1->addTransition(S8_2, nav->previousCalled);
    S8_1->addTransition(S9_0, nav->confirmSeedScreenCalled);
    S8_2->addTransition(S8_1, nav->nextCalled);
    S8_2->addTransition(S8_0, nav->firstSeedScreenCalled);
    S9_0->addTransition(S9_1, nav->btConnectedCalled);
    S9_1->addTransition(S9_2, nav->receivedTxCalled);
    S9_1->addTransition(S9_0, nav->btDisconnectedCalled);
    S9_2->addTransition(S9_3, nav->nextCalled);
    S9_2->addTransition(S9_1, nav->bothCalled);
    S9_2->addTransition(S9_0, nav->btDisconnectedCalled);
    S9_3->addTransition(S9_4, nav->bothCalled);
    S9_3->addTransition(S9_0, nav->btDisconnectedCalled);
    S9_3->addTransition(S9_2, nav->previousCalled);
    S9_4->addTransition(S9_1, nav->bothCalled);

}

void Menu::run() {
    machine.run();
}

