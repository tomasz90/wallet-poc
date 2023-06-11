#ifndef SIGNER_H
#define SIGNER_H

#include "util/Repository.h"

class Signer {
public:
    Repository *repository;
    explicit Signer(Repository *repository) : repository(repository) {}
    void sign(EthTx *tx, string &key, char *&buffer);
private:
    DynamicJsonBuffer jb;
};


#endif //SIGNER_H
