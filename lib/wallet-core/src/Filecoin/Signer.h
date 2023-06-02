// Copyright © 2017-2023 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Transaction.h"

#include "Data.h"
#include "../Hash.h"
#include "../PrivateKey.h"
#include "../proto/Filecoin.pb.h"

namespace TW::Filecoin {

/// Helper class that performs Filecoin transaction signing.
class Signer {
  public:
    Signer() = delete;

    /// Signs a Proto::SigningInput transaction.
    static Proto::SigningOutput sign(const Proto::SigningInput& input) noexcept;

    /// Signs a json Proto::SigningInput with private key
    static std::string signJSON(const std::string& json, const Data& key);

    /// Signs the given transaction.
    static Data sign(const PrivateKey& privateKey, Transaction& transaction) noexcept;

private:
    /// Signs a Proto::SigningInput transaction.
    static Proto::SigningOutput signSecp256k1(const Proto::SigningInput& input);

    /// Signs a Proto::SigningInput transaction.
    static Proto::SigningOutput signDelegated(const Proto::SigningInput& input);
};

} // namespace TW::Filecoin
