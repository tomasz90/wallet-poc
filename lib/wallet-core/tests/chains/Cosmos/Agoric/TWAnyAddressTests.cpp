// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../CosmosTestHelpers.h"

namespace TW::Cosmos::tests {

static const std::string gAgoricAddr = "agoric1wu32wujsvz290sasq308fswznx77nk9k0cxqwg";
static const std::string gAgoricHrp = "agoric";

TEST(TWAgoricAnyAddress, AllAgoricAddressTests) {
    CosmosAddressParameters parameters{.hrp = gAgoricHrp,
                                       .coinType = TWCoinTypeAgoric,
                                       .address = gAgoricAddr,
                                       .privKey = "9457d0a4b7bdfe23528af07603af0f7d0ac0c510526da7721abefdc3948461f6",
                                       .publicKey = "03602731bc2f787eec358c1ba8ddb8e7c7720f56a0406b8d16e20c93b822953960"};
    TestCosmosAddressParameters(parameters);
}

} // namespace TW::Cosmos::tests
