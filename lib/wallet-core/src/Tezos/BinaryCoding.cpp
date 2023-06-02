// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../Base58.h"
#include "Data.h"
#include "../HexCoding.h"
#include "../PublicKey.h"
#include "../PrivateKey.h"

#include <TrezorCrypto/ecdsa.h>
#include <string>

namespace TW::Tezos {

std::string base58ToHex(const std::string& string, size_t prefixLength) {
    const auto decoded = Base58::decodeCheck(string);
    if (decoded.size() < prefixLength) {
        return "";
    }
    Data v(decoded.data() + prefixLength, decoded.data() + decoded.size());
    return TW::hex(v);
}

PublicKey parsePublicKey(const std::string& publicKey) {
    const auto decoded = Base58::decodeCheck(publicKey);

    std::array<byte, 4> prefix = {13, 15, 37, 217};
    auto pk = Data();

    if (decoded.size() != 32 + prefix.size()) {
        throw std::invalid_argument("Invalid Public Key");
    }
    append(pk, Data(decoded.begin() + prefix.size(), decoded.end()));

    return PublicKey(pk, TWPublicKeyTypeED25519);
}

PrivateKey parsePrivateKey(const std::string& privateKey) {
    const auto decoded = Base58::decodeCheck(privateKey);
    auto pk = Data();
    auto prefix_size = 4ul;

    if (decoded.size() != 32 + prefix_size) {
        throw std::invalid_argument("Invalid Public Key");
    }
    append(pk, Data(decoded.begin() + prefix_size, decoded.end()));
    return PrivateKey(pk);
}

} // namespace TW::Tezos
