#ifndef ETHEREUMHDPUBLICKEY_H
#define ETHEREUMHDPUBLICKEY_H

#include <cstdint>
#include <cstddef>
#include "Bitcoin.h"

class EthereumHDPublicKey : HDPublicKey {
public:
    explicit EthereumHDPublicKey(const HDPublicKey &hd);

    size_t to_bytes(uint8_t *arr, size_t len) const;
};


#endif //ETHEREUMHDPUBLICKEY_H
