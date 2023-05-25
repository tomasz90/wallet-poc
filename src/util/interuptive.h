#include <esp_attr.h>

#ifndef WALLET_POC_INTERUPTIVE_H
#define WALLET_POC_INTERUPTIVE_H

#endif //WALLET_POC_INTERUPTIVE_H

class Interaptive {
public:
    static int wordIndex;
    static void (*nextWord())();
private:
    static unsigned long lastButtonTime;
    Interaptive();
    static void innerNextWord();
};
