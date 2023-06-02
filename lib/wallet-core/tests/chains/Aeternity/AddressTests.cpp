// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <Aeternity/Address.h>
#include <HexCoding.h>
#include <gtest/gtest.h>

namespace TW::Aeternity::tests {

TEST(AeternityAddress, FromPublicKey) {
    auto publicKey = PublicKey(parse_hex("ee93a4f66f8d16b819bb9beb9ffccdfcdc1412e87fee6a324c2a99a1e0e67148"), TWPublicKeyTypeED25519);
    auto address = Address(publicKey);
    ASSERT_EQ(address.string(), "ak_2p5878zbFhxnrm7meL7TmqwtvBaqcBddyp5eGzZbovZ5FeVfcw");
    ASSERT_ANY_THROW(Address(PublicKey(parse_hex("03df9a5e4089f89d45913fb2b856de984c7e8bf1344cc6444cc9705899a48c939d"), TWPublicKeyTypeSECP256k1)));
}

TEST(AeternityAddress, FromString) {
    auto address = Address("ak_2p5878zbFhxnrm7meL7TmqwtvBaqcBddyp5eGzZbovZ5FeVfcw");
    ASSERT_EQ(address.string(), "ak_2p5878zbFhxnrm7meL7TmqwtvBaqcBddyp5eGzZbovZ5FeVfcw");
    ASSERT_ANY_THROW(Address("invalid"));
}

} // namespace TW::Aeternity::tests
