// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Entry.h"

#include "Address.h"
#include "Signer.h"

namespace TW::Zilliqa {

// Note: avoid business logic from here, rather just call into classes like Address, Signer, etc.

bool Entry::validateAddress([[maybe_unused]] TWCoinType coin, const std::string& address, [[maybe_unused]] const PrefixVariant& addressPrefix) const {
    return Address::isValid(address);
}

std::string Entry::deriveAddress([[maybe_unused]] TWCoinType coin, const PublicKey& publicKey, [[maybe_unused]] TWDerivation derivation, [[maybe_unused]] const PrefixVariant& addressPrefix) const {
    return Address(publicKey).string();
}

Data Entry::addressToData([[maybe_unused]] TWCoinType coin, const std::string& address) const {
    Address addr;
    if (!Address::decode(address, addr)) {
        return {};
    }
    // data in Zilliqa is a checksummed string without 0x
    return data(checksum(addr.getKeyHash()));
}

void Entry::sign([[maybe_unused]] TWCoinType coin, const Data& dataIn, Data& dataOut) const {
    signTemplate<Signer, Proto::SigningInput>(dataIn, dataOut);
}

std::string Entry::signJSON([[maybe_unused]] TWCoinType coin, const std::string& json, const Data& key) const {
    return Signer::signJSON(json, key);
}

} // namespace TW::Zilliqa
