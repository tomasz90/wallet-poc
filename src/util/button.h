//
// Created by Tomasz Kulig on 26/05/2023.
//

#ifndef WALLET_POC_BUTTON_H
#define WALLET_POC_BUTTON_H

#endif //WALLET_POC_BUTTON_H

class Button {
public:
    Button();
    bool isPendingClick();
    void setPending();
    bool isActive();
    void setClicked();

    bool canBeClicked();

private:
    bool pendingClick;
    unsigned long plannedMillisClick;
};
