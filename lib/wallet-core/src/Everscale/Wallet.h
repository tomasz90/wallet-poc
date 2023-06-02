// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <boost/integer.hpp>
#include <utility>

#include "PublicKey.h"

#include "Address.h"
#include "CommonTON/Cell.h"
#include "CommonTON/CellBuilder.h"
#include "CommonTON/CellSlice.h"
#include "CommonTON/Messages.h"

const uint32_t WALLET_ID = 0x4BA92D8A;

using namespace TW::CommonTON;

namespace TW::Everscale {

class Wallet {
public:
    enum MessageFlags : uint8_t {
        // Sender wants to pay transfer fees separately
        // (from account balance instead of message balance)
        FeesFromAccountBalance = (1 << 0),

        // If there are some errors during the action phase it should be ignored
        IgnoreActionPhaseErrors = (1 << 1),

        // Message will carry all the remaining balance
        AttachAllBalance = (1 << 7),
    };

    struct Gift {
        bool bounce;
        uint64_t amount;
        Address to;
        uint8_t flags;
    };

    static constexpr uint8_t simpleTransferFlags =
        MessageFlags::FeesFromAccountBalance | MessageFlags::IgnoreActionPhaseErrors;
    static constexpr uint8_t sendAllBalanceFlags =
        MessageFlags::AttachAllBalance | MessageFlags::IgnoreActionPhaseErrors;

    static const Data code;
};

class InitData {
    uint32_t _seqno;
    uint32_t _walletId;
    PublicKey _publicKey;

public:
    explicit InitData(PublicKey publicKey)
        : _seqno(0), _walletId(WALLET_ID), _publicKey(std::move(publicKey)) {}
    explicit InitData(CellSlice cs)
        : _seqno(cs.getNextU32()), _walletId(cs.getNextU32()), _publicKey(PublicKey(cs.getNextBytes(32), TWPublicKeyTypeED25519)) {}

    [[nodiscard]] CellBuilder writeTo() const;
    [[nodiscard]] StateInit makeStateInit() const;
    [[nodiscard]] AddressData computeAddr(int8_t workchainId) const;
    [[nodiscard]] CellBuilder makeTransferPayload(uint32_t expireAt, const Wallet::Gift& gift) const;
};

} // namespace TW::Everscale
