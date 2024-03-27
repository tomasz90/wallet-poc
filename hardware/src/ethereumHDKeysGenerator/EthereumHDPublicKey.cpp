#include <cstring>
#include "EthereumHDPublicKey.h"
#include "Bitcoin.h"

EthereumHDPublicKey::EthereumHDPublicKey(const HDPublicKey &hd) : HDPublicKey(hd) {}

size_t EthereumHDPublicKey::to_bytes(uint8_t *arr, size_t len) const {
    // practically a copy of HDPublicKey::to_bytes(uint8_t *arr, size_t len) const, since that fn is private
    uint8_t hex[78] = { 0 };
    memcpy(hex, network->xpub, 4);
    hex[4] = depth;
    memcpy(hex+5, parentFingerprint, 4);
    for(uint8_t i=0; i<4; i++){
        hex[12-i] = ((childNumber >> (i*8)) & 0xFF);
    }
    memcpy(hex+13, chainCode, 32);
    memcpy(hex+46, point, 32);
    hex[45] = 0x02 + (point[63] & 0x01);
    if(len > sizeof(hex)){
        len = sizeof(hex);
    }
    memcpy(arr, hex, len);
    return len;
}
