// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Oep4TxBuilder.h"
#include "../HexCoding.h"

namespace TW::Ontology {

Data Oep4TxBuilder::decimals(const Ontology::Proto::SigningInput& input) {
    Oep4 oep4(parse_hex(input.contract()));
    auto transaction = oep4.decimals(input.nonce());
    auto encoded = transaction.serialize();
    return encoded;
}

Data Oep4TxBuilder::balanceOf(const Ontology::Proto::SigningInput& input) {
    Oep4 oep4(parse_hex(input.contract()));
    auto queryAddress = Address(input.query_address());
    auto transaction = oep4.balanceOf(queryAddress, input.nonce());
    auto encoded = transaction.serialize();
    return encoded;
}

Data Oep4TxBuilder::transfer(const Ontology::Proto::SigningInput& input) {
    Oep4 oep4(parse_hex(input.contract()));
    auto payerSigner = Signer(PrivateKey(input.payer_private_key()));
    auto fromSigner = Signer(PrivateKey(input.owner_private_key()));
    auto toAddress = Address(input.to_address());
    auto tranferTx = oep4.transfer(fromSigner, toAddress, input.amount(), payerSigner,
                                   input.gas_price(), input.gas_limit(), input.nonce());
    auto encoded = tranferTx.serialize();
    return encoded;
}

Data Oep4TxBuilder::build(const Ontology::Proto::SigningInput& input) {
    auto method = std::string(input.method().begin(), input.method().end());
    if (method == "transfer") {
        return Oep4TxBuilder::transfer(input);
    } else if (method == "balanceOf") {
        return Oep4TxBuilder::balanceOf(input);
    } else if (method == "decimals") {
        return Oep4TxBuilder::decimals(input);
    }

    return Data();
}

} // namespace TW::Ontology
