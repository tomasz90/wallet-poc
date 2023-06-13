#ifndef SIGNER_H
#define SIGNER_H

#include "EthTx.h"

using std::string;

class Signer {
public:
    void sign(EthTx *tx, string &key, char *&buffer);
private:
    DynamicJsonBuffer jb;
};


#endif //SIGNER_H
