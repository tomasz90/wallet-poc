// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Swap.h"

#include "Coin.h"
#include "HexCoding.h"
#include <TrustWalletCore/TWCoinType.h>

// ATOM
#include "Cosmos/Address.h"
#include "../proto/Cosmos.pb.h"
// BTC
#include "Bitcoin/SigHashType.h"
#include "../proto/Bitcoin.pb.h"
// ETH
#include "Ethereum/ABI/Function.h"
#include "Ethereum/ABI/ParamAddress.h"
#include "Ethereum/ABI/ParamBase.h"
#include "Ethereum/Address.h"
#include "uint256.h"
#include "../proto/Ethereum.pb.h"
// BNB
#include "Binance/Address.h"
#include "../proto/Binance.pb.h"

#include <cstdlib>

/*
 * References:
 *  https://gitlab.com/thorchain/asgardex-common/asgardex-util
 */

namespace TW::THORChainSwap {

static Data ethAddressStringToData(const std::string& asString) {
    Data asData(20);
    if (asString.empty() || !Ethereum::Address::isValid(asString)) {
        return asData;
    }
    auto address = Ethereum::Address(asString);
    std::copy(address.bytes.begin(), address.bytes.end(), asData.data());
    return asData;
}

TWCoinType chainCoinType(Chain chain) {
    switch (chain) {
    case Chain::ETH:
        return TWCoinTypeEthereum;
    case Chain::AVAX:
        return TWCoinTypeAvalancheCChain;
    case Chain::BNB:
        return TWCoinTypeBinance;
    case Chain::BTC:
        return TWCoinTypeBitcoin;
    case Chain::DOGE:
        return TWCoinTypeDogecoin;
    case Chain::BCH:
        return TWCoinTypeBitcoinCash;
    case Chain::LTC:
        return TWCoinTypeLitecoin;
    case Chain::ATOM:
        return TWCoinTypeCosmos;
    case Chain::THOR:
    default:
        return TWCoinTypeTHORChain;
    }
}

std::string chainName(Chain chain) {
    switch (chain) {
    case Chain::AVAX:
        return "AVAX";
    case Chain::ETH:
        return "ETH";
    case Chain::BNB:
        return "BNB";
    case Chain::BTC:
        return "BTC";
    case Chain::DOGE:
        return "DOGE";
    case Chain::BCH:
        return "BCH";
    case Chain::LTC:
        return "LTC";
    case Chain::ATOM:
        return "GAIA";
    case Chain::THOR:
    default:
        return "THOR";
    }
}

bool validateAddress(Chain chain, const std::string& address) {
    return TW::validateAddress(chainCoinType(chain), address);
}

SwapBundled SwapBuilder::build(bool shortened) {
    auto fromChain = static_cast<Chain>(mFromAsset.chain());
    auto toChain = static_cast<Chain>(mToAsset.chain());

    if (!validateAddress(fromChain, mFromAddress)) {
        return {.status_code = static_cast<SwapErrorCode>(Proto::ErrorCode::Error_Invalid_from_address), .error = "Invalid from address"};
    }
    if (!validateAddress(toChain, mToAddress)) {
        return {.status_code = static_cast<SwapErrorCode>(Proto::ErrorCode::Error_Invalid_to_address), .error = "Invalid to address"};
    }

    uint256_t fromAmountNum = uint256_t(mFromAmount);
    const auto memo = this->buildMemo(shortened);

    switch (fromChain) {
    case Chain::BTC:
    case Chain::DOGE:
    case Chain::BCH:
    case Chain::LTC: {
        return buildBitcoin(fromAmountNum, memo, fromChain);
    case Chain::BNB:
        return buildBinance(mFromAsset, fromAmountNum, memo);
    case Chain::ATOM:
        return buildAtom(fromAmountNum, memo);
    case Chain::ETH:
    case Chain::AVAX:
        return buildEth(fromAmountNum, memo);
    }
    default:
        return {.status_code = static_cast<SwapErrorCode>(Proto::ErrorCode::Error_Unsupported_from_chain), .error = "Unsupported from chain: " + std::to_string(fromChain)};
    }
}
std::string SwapBuilder::buildMemo(bool shortened) noexcept {
    uint64_t toAmountLimitNum = std::stoull(mToAmountLimit);

    // Memo: 'SWAP', or shortened '='; see https://dev.thorchain.org/thorchain-dev/concepts/memos
    std::string prefix = shortened ? "=" : "SWAP";
    const auto& toChain = static_cast<Chain>(mToAsset.chain());
    const auto& toTokenId = mToAsset.token_id();
    const auto& toSymbol = mToAsset.symbol();
    const auto toCoinToken = (!toTokenId.empty() && toTokenId != "0x0000000000000000000000000000000000000000") ? toTokenId : toSymbol;
    std::stringstream memo;
    memo << prefix + ":" + chainName(toChain) + "." + toCoinToken + ":" + mToAddress;
    if (toAmountLimitNum > 0) {
        memo << ":" << std::to_string(toAmountLimitNum);
    }

    if (mAffFeeAddress.has_value() || mAffFeeRate.has_value() || mExtraMemo.has_value()) {
        memo << ":";
        if (mAffFeeAddress.has_value()) {
            memo << mAffFeeAddress.value();
        }
        if (mAffFeeRate.has_value() || mExtraMemo.has_value()) {
            memo << ":";
            if (mAffFeeRate.has_value()) {
                memo << mAffFeeRate.value();
            }
            if (mExtraMemo.has_value()) {
                memo << ":" << mExtraMemo.value();
            }
        }
    }

    return memo.str();
}

SwapBundled SwapBuilder::buildBitcoin(uint256_t amount, const std::string& memo, Chain fromChain) {
    auto input = Bitcoin::Proto::SigningInput();
    Data out;
    // Following fields must be set afterwards, before signing ...
    auto coinType = chainCoinType(fromChain);
    input.set_hash_type(Bitcoin::hashTypeForCoin(coinType));
    input.set_byte_fee(1);
    input.set_use_max_amount(false);
    // private_key[]
    // utxo[]
    // scripts[]
    // ... end

    input.set_amount(static_cast<int64_t>(amount));
    input.set_to_address(mVaultAddress);
    input.set_change_address(mFromAddress);
    input.set_coin_type(coinType);
    input.set_output_op_return(memo);

    auto serialized = input.SerializeAsString();
    out.insert(out.end(), serialized.begin(), serialized.end());
    return {.out = std::move(out)};
}
SwapBundled SwapBuilder::buildBinance(Proto::Asset fromAsset, uint256_t amount, const std::string& memo) {
    auto input = Binance::Proto::SigningInput();
    Data out;

    // Following fields must be set afterwards, before signing ...
    input.set_chain_id("");
    input.set_account_number(0);
    input.set_sequence(0);
    input.set_source(0);
    input.set_private_key("");
    // ... end

    input.set_memo(memo);

    auto& order = *input.mutable_send_order();

    auto token = Binance::Proto::SendOrder::Token();
    token.set_denom(fromAsset.token_id().empty() ? "BNB" : fromAsset.token_id());
    token.set_amount(static_cast<uint64_t>(amount));
    {
        Binance::Address fromAddressBin;
        Binance::Address::decode(mFromAddress, fromAddressBin);
        auto input_ = order.add_inputs();
        input_->set_address(fromAddressBin.getKeyHash().data(), fromAddressBin.getKeyHash().size());
        *input_->add_coins() = token;
    }
    {
        Binance::Address vaultAddressBin;
        Binance::Address::decode(mVaultAddress, vaultAddressBin);
        auto output = order.add_outputs();
        output->set_address(vaultAddressBin.getKeyHash().data(), vaultAddressBin.getKeyHash().size());
        *output->add_coins() = token;
    }

    auto serialized = input.SerializeAsString();
    out.insert(out.end(), serialized.begin(), serialized.end());
    return {.out = std::move(out)};
}

SwapBundled SwapBuilder::buildEth(uint256_t amount, const std::string& memo) {
    Data out;
    auto input = Ethereum::Proto::SigningInput();
    // EIP-1559
    input.set_tx_mode(Ethereum::Proto::Enveloped);
    const auto& toTokenId = mFromAsset.token_id();
    // some sanity check / address conversion
    Data vaultAddressBin = ethAddressStringToData(mVaultAddress);
    if (!Ethereum::Address::isValid(mVaultAddress) || vaultAddressBin.size() != Ethereum::Address::size) {
        return {.status_code = static_cast<int>(Proto::ErrorCode::Error_Invalid_vault_address), .error = "Invalid vault address: " + mVaultAddress};
    }
    if (!toTokenId.empty() && !Ethereum::Address::isValid(*mRouterAddress)) {
        return {.status_code = static_cast<int>(Proto::ErrorCode::Error_Invalid_router_address), .error = "Invalid router address: " + *mRouterAddress};
    }
    Data toAssetAddressBin = ethAddressStringToData(toTokenId);

    // Following fields must be set afterwards, before signing ...
    const auto chainId = store(uint256_t(0));
    input.set_chain_id(chainId.data(), chainId.size());
    const auto nonce = store(uint256_t(0));
    input.set_nonce(nonce.data(), nonce.size());
    const auto gasPrice = store(uint256_t(0));
    input.set_gas_price(gasPrice.data(), gasPrice.size());
    const auto gasLimit = store(uint256_t(0));
    input.set_gas_limit(gasLimit.data(), gasLimit.size());
    input.set_private_key("");
    // ... end

    input.set_to_address(*mRouterAddress);
    if (!toTokenId.empty()) {
        if (!mExpirationPolicy) {
            std::cout << "here"<< std::endl;
            auto now = std::chrono::system_clock::now();
            auto in_15_minutes = now + std::chrono::minutes(15);
            mExpirationPolicy = std::chrono::duration_cast<std::chrono::seconds>(in_15_minutes.time_since_epoch()).count();
        }
        auto& transfer = *input.mutable_transaction()->mutable_contract_generic();
        auto func = Ethereum::ABI::Function("depositWithExpiry", std::vector<std::shared_ptr<Ethereum::ABI::ParamBase>>{
                                                                     std::make_shared<Ethereum::ABI::ParamAddress>(vaultAddressBin),
                                                                     std::make_shared<Ethereum::ABI::ParamAddress>(toAssetAddressBin),
                                                                     std::make_shared<Ethereum::ABI::ParamUInt256>(uint256_t(amount)),
                                                                     std::make_shared<Ethereum::ABI::ParamString>(memo),
                                                                     std::make_shared<Ethereum::ABI::ParamUInt256>(uint256_t(*mExpirationPolicy))});
        Data payload;
        func.encode(payload);
        transfer.set_data(payload.data(), payload.size());
        Data amountData = store(uint256_t(0));
        transfer.set_amount(amountData.data(), amountData.size());
    } else {
        input.set_to_address(mVaultAddress);
        auto& transfer = *input.mutable_transaction()->mutable_transfer();
        Data amountData = store(uint256_t(amount));
        transfer.set_amount(amountData.data(), amountData.size());
        transfer.set_data(memo.data(), memo.size());
    }

    auto serialized = input.SerializeAsString();
    out.insert(out.end(), serialized.begin(), serialized.end());
    return {.out = std::move(out)};
}

SwapBundled SwapBuilder::buildAtom(uint256_t amount, const std::string& memo) {
    if (!Cosmos::Address::isValid(mVaultAddress, "cosmos")) {
        return {.status_code = static_cast<int>(Proto::ErrorCode::Error_Invalid_vault_address), .error = "Invalid vault address: " + mVaultAddress};
    }
    Data out;

    auto input = Cosmos::Proto::SigningInput();
    input.set_signing_mode(Cosmos::Proto::Protobuf);
    input.set_chain_id("cosmoshub-4");
    input.set_memo(memo);

    auto msg = input.add_messages();
    auto& message = *msg->mutable_send_coins_message();

    message.set_from_address(mFromAddress);
    message.set_to_address(mVaultAddress);

    auto amountOfTx = message.add_amounts();
    amountOfTx->set_denom("uatom");
    amountOfTx->set_amount(amount.str());

    auto serialized = input.SerializeAsString();
    out.insert(out.end(), serialized.begin(), serialized.end());

    return {.out = std::move(out)};
}

} // namespace TW::THORChainSwap
