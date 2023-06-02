// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Data.h"
#include "PublicKey.h"

#include "CommonTON/RawAddress.h"

#include <optional>
#include <string>

namespace TW::Everscale {

using AddressData = CommonTON::AddressData;

class Address {
public:
    AddressData addressData;

    /// Determines whether a string makes a valid address.
    [[nodiscard]] static bool isValid(const std::string& string) noexcept;

    /// Initializes an Everscale address with a string representation.
    explicit Address(const std::string& string);

    /// Initializes an Everscale address with a public key and a workchain id.
    explicit Address(const PublicKey& publicKey, int8_t workchainId);

    /// Initializes an Everscale address with its parts
    explicit Address(int8_t workchainId, std::array<byte, AddressData::size> hash)
        : addressData(workchainId, hash) {}

    /// Initializes an Everscale address with AddressData
    explicit Address(AddressData addressData)
        : addressData(addressData) {}

    /// Returns a string representation of the address.
    [[nodiscard]] std::string string() const;
};

inline bool operator==(const Address& lhs, const Address& rhs) {
    return lhs.addressData.workchainId == rhs.addressData.workchainId && lhs.addressData.hash == rhs.addressData.hash;
}

} // namespace TW::Everscale
