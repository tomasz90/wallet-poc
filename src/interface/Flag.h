#ifndef WALLET_POC_FLAG_H
#define WALLET_POC_FLAG_H

struct Flag {
    bool flag = false;
    bool check();
    void set();
    void unset();
};


#endif //WALLET_POC_FLAG_H
