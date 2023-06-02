// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWCardano.h>

#include "Cardano/Transaction.h"
#include "Cardano/AddressV3.h"
#include "proto/Cardano.pb.h"

using namespace TW;

uint64_t TWCardanoMinAdaAmount(TWData *_Nonnull tokenBundle) {
    const Data* bundleData = static_cast<const Data*>(tokenBundle);
    TW::Cardano::Proto::TokenBundle bundleProto;
    if (bundleData && bundleProto.ParseFromArray(bundleData->data(), (int)bundleData->size())) {
        return TW::Cardano::TokenBundle::fromProto(bundleProto).minAdaAmount();
    }
    return 0;
}

uint64_t TWCardanoOutputMinAdaAmount(TWString *_Nonnull toAddress, TWData *_Nonnull tokenBundle, uint64_t coinsPerUtxoByte) {
    const std::string& address = *reinterpret_cast<const std::string*>(toAddress);
    const Data* bundleData = static_cast<const Data*>(tokenBundle);

    try {
        // Set the initial amount to 0.
        const uint64_t amount = 0;
        const TW::Cardano::AddressV3 cardanoAddress(address);

        TW::Cardano::Proto::TokenBundle bundleProto;
        if (!bundleData || !bundleProto.ParseFromArray(bundleData->data(), (int)bundleData->size())) {
            // Expect at least an empty `TokenBundle`.
            return 0;
        }
        const auto tokens = TW::Cardano::TokenBundle::fromProto(bundleProto);

        const TW::Cardano::TxOutput output(cardanoAddress.data(), amount, tokens);
        return output.minAdaAmount(coinsPerUtxoByte);
    } catch (...) {
        return 0;
    }
}

TWString *_Nonnull TWCardanoGetStakingAddress(TWString *_Nonnull baseAddress) {
    const auto& address = *reinterpret_cast<const std::string*>(baseAddress);
    try {
        return TWStringCreateWithUTF8Bytes(TW::Cardano::AddressV3(address).getStakingAddress().c_str());
    } catch (...) {
        return TWStringCreateWithUTF8Bytes("");
    }
}
