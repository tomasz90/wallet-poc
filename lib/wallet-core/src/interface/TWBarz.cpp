// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWBarz.h>
#include <TrustWalletCore/TWData.h>
#include <string>
#include "Ethereum/Barz.h"

TWString *_Nonnull TWBarzGetCounterfactualAddress(TWData *_Nonnull input) {
    TW::Barz::Proto::ContractAddressInput inputProto;

    const auto bytes = TWDataBytes(input);
    const auto size = static_cast<int>(TWDataSize(input));
    if (!inputProto.ParseFromArray(bytes, size)) {
        return "";
    }

    return TWStringCreateWithUTF8Bytes(TW::Barz::getCounterfactualAddress(inputProto).c_str());
}

TWData *_Nonnull TWBarzGetInitCodeFromPublicKey(TWString* _Nonnull factory, TWString* _Nonnull publicKey, TWString* _Nonnull verificationFacet) {
    const auto& factoryStr = *reinterpret_cast<const std::string*>(factory);
    const auto& publicKeyStr = *reinterpret_cast<const std::string*>(publicKey);
    const auto& verificationFacetStr = *reinterpret_cast<const std::string*>(verificationFacet);

    const auto initCode = TW::Barz::getInitCodeFromPublicKey(factoryStr, publicKeyStr, verificationFacetStr);
    return TWDataCreateWithData(&initCode);
}

TWData *_Nonnull TWBarzGetInitCodeFromAttestationObject(TWString* _Nonnull factory, TWString* _Nonnull attestationObject, TWString* _Nonnull verificationFacet) {
    const auto& factoryStr = *reinterpret_cast<const std::string*>(factory);
    const auto& attestationObjectStr = *reinterpret_cast<const std::string*>(attestationObject);
    const auto& verificationFacetStr = *reinterpret_cast<const std::string*>(verificationFacet);
    const auto initCode = TW::Barz::getInitCodeFromAttestationObject(factoryStr, attestationObjectStr, verificationFacetStr);
    return TWDataCreateWithData(&initCode);
}