//
// Created by Tomasz Kulig on 26/05/2023.
//

#ifndef WALLET_POC_BUTTON_H
#define WALLET_POC_BUTTON_H

#endif //WALLET_POC_BUTTON_H

class Button {
public:
    explicit Button(std::string name);
    bool isPendingClick() const;
    void setPending();
    void setClicked();
    bool canBeClicked() const;
    std::string getName();

private:
    std::string name;
    bool pendingClick;
    unsigned long plannedMillisClick;
};
