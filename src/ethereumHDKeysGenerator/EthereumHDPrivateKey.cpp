#include "EthereumHDPrivateKey.h"
#include "EthereumHDPublicKey.h"
#include "utility/trezor/memzero.h"
#include "utility/trezor/sha3.h"

EthereumHDPrivateKey::EthereumHDPrivateKey(const String &mnemonic) : EthereumHDPrivateKey(mnemonic, "") {}

EthereumHDPrivateKey::EthereumHDPrivateKey(const String &mnemonic, const String &password) :
        HDPrivateKey(mnemonic, password) {}

EthereumHDPrivateKey::EthereumHDPrivateKey(const HDPrivateKey &hd) : HDPrivateKey(hd) {}

EthereumHDPrivateKey EthereumHDPrivateKey::derive(const String &path) const {
    HDPrivateKey hd = HDPrivateKey::derive(path);
    return EthereumHDPrivateKey(hd);
}

String EthereumHDPrivateKey::xprv() const {
    return HDPrivateKey::xprv();
}

String EthereumHDPrivateKey::xpub() const {
    return HDPrivateKey::xpub();
}

String EthereumHDPrivateKey::pub() const {
    uint8_t xpubRaw[78];
    EthereumHDPublicKey pubKey = EthereumHDPublicKey(HDPrivateKey::xpub());
    pubKey.to_bytes(xpubRaw, sizeof(xpubRaw));

    uint8_t pubRaw[33] = {0};
    fromBase58(this->xprv(), pubRaw, sizeof(pubRaw));

    memcpy(pubRaw, xpubRaw + sizeof(xpubRaw) - sizeof(pubRaw), sizeof(pubRaw));
    memzero(&xpubRaw, sizeof(xpubRaw));

    return "0x" + toHex(pubRaw, sizeof(pubRaw));
}

String EthereumHDPrivateKey::prv() const {
    uint8_t last32Bytes[32] = {0};
    prvRaw(last32Bytes, sizeof(last32Bytes));

    String prv = "0x" + toHex(last32Bytes, sizeof(last32Bytes));
    memzero(&last32Bytes, sizeof(last32Bytes));
    return prv;
}

String EthereumHDPrivateKey::addressChecksumed() const {
    uint8_t addr[20] = {0};
    rawAddress(addr, sizeof(addr));

    String addrString = toHex(addr, sizeof(addr));
    const auto *addrChar = reinterpret_cast<const unsigned char *>(addrString.c_str());

    uint8_t hash[32] = {0};
    keccak_256(addrChar, 40, hash);

    String hashString = toHex(hash, sizeof(hash));

    for (int i = 0; i < addrString.length(); i++) {
        if (addrString[i] >= 'a') {
            if (hashString[i] >= '8') {
                addrString[i] = toUpperCase(addrString[i]);
            }
        }
    }

    return "0x" + addrString;
}

String EthereumHDPrivateKey::address() const {
    uint8_t address[20] = {0};
    rawAddress(address, sizeof(address));
    return "0x" + toHex(address, sizeof(address));
}

void EthereumHDPrivateKey::prvRaw(uint8_t *result, uint8_t resultSize) const {
    uint8_t xprvRaw[78] = {0};
    size_t l = fromBase58Check(this->xprv(), xprvRaw, sizeof(xprvRaw));

    if (l != sizeof(xprvRaw)) {
        Serial.println("Invalid xprv conversion");
        return;
    }
    memcpy(result, xprvRaw + sizeof(xprvRaw) - resultSize, resultSize);
    memzero(&xprvRaw, sizeof(xprvRaw));
}

void EthereumHDPrivateKey::rawAddress(uint8_t *rawAddress, uint8_t rawAddressLength) const {

    HDPublicKey pubKey = HDPrivateKey::xpub();
    uint8_t hash[32] = {0};

    keccak_256(pubKey.point, sizeof(pubKey.point), hash);

    memcpy(rawAddress, hash + sizeof(hash) - rawAddressLength, rawAddressLength);
    memzero(&hash, sizeof(hash));
}
