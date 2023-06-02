// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWStarkExMessageSigner.h>

#include "StarkEx/MessageSigner.h"

TWString* _Nonnull TWStarkExMessageSignerSignMessage(const struct TWPrivateKey* _Nonnull privateKey, TWString* _Nonnull message) {
    try {
        const auto signature = TW::StarkEx::MessageSigner::signMessage(privateKey->impl, TWStringUTF8Bytes(message));
        return TWStringCreateWithUTF8Bytes(signature.c_str());
    } catch (...) {
        return TWStringCreateWithUTF8Bytes("");
    }
}

bool TWStarkExMessageSignerVerifyMessage(const struct TWPublicKey* _Nonnull publicKey, TWString* _Nonnull message, TWString* _Nonnull signature) {
    return TW::StarkEx::MessageSigner::verifyMessage(publicKey->impl, TWStringUTF8Bytes(message), TWStringUTF8Bytes(signature));
}
