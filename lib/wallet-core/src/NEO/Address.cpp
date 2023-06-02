// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "OpCode.h"
#include "../Base58.h"
#include "Data.h"
#include "../Hash.h"
#include "../Ontology/ParamsBuilder.h"

#include "Address.h"

using namespace TW;

namespace TW::NEO {

bool Address::isValid(const std::string& string) {
    const auto decoded = Base58::decodeCheck(string);
    return !(decoded.size() != Address::size || decoded[0] != version);
}

Address::Address() {
    Data keyHash;
    for (auto i = 0ul; i < Address::size; i++) {
        keyHash.push_back(0);
    }
    std::copy(keyHash.data(), keyHash.data() + Address::size, bytes.begin());
}

Address::Address(const PublicKey& publicKey) {
    auto publicKeyData = publicKey.bytes;

    auto pkdata = Data(publicKeyData.begin(), publicKeyData.end());
    pkdata.insert(pkdata.begin(), PUSHBYTES21);
    pkdata.push_back(CHECKSIG);

    auto keyHash = Hash::ripemd(Hash::sha256(pkdata));
    keyHash.insert(keyHash.begin(), (byte)Address::version);

    if (keyHash.size() != Address::size) {
        throw std::invalid_argument("Invalid address key data");
    }

    std::copy(keyHash.data(), keyHash.data() + Address::size, bytes.begin());
}

Address::Address(uint8_t m, const std::vector<Data>& publicKeys) {
    auto builderData = toScriptHash(Ontology::ParamsBuilder::fromMultiPubkey(m, publicKeys));
    std::copy(builderData.begin(), builderData.end(), bytes.begin());
}

Data Address::toScriptHash(const Data& data) const {
    return Hash::ripemd(Hash::sha256(data));
}

Data Address::toScriptHash() const {
    byte buf[Hash::ripemdSize];
    Data data(buf, buf + Hash::ripemdSize);
    std::copy(bytes.begin() + 1, bytes.begin() + Hash::ripemdSize + 1, data.begin());
    return data;
}

} // namespace TW::NEO
