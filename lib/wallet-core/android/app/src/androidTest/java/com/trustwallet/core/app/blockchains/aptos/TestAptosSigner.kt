// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

package com.trustwallet.core.app.blockchains.aptos

import com.google.protobuf.ByteString
import com.trustwallet.core.app.utils.Numeric
import com.trustwallet.core.app.utils.toHexByteArray
import com.trustwallet.core.app.utils.toHexBytes
import com.trustwallet.core.app.utils.toHexBytesInByteString
import org.junit.Assert.assertEquals
import org.junit.Test
import wallet.core.java.AnySigner
import wallet.core.jni.CoinType
import wallet.core.jni.proto.Aptos

class TestAptosSigner {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    @Test
    fun AptosTransactionBlindSigning() {
        // Successfully broadcasted: https://explorer.aptoslabs.com/txn/0x7efd69e7f9462774b932ce500ab51c0d0dcc004cf272e09f8ffd5804c2a84e33?network=mainnet
        val key =
            "5d996aa76b3212142792d9130796cd2e11e3c445a93118c08414df4f66bc60ec".toHexBytesInByteString()

        val payloadJson = """
            {
                    "function": "0x16fe2df00ea7dde4a63409201f7f4e536bde7bb7335526a35d05111e68aa322c::AnimeSwapPoolV1::swap_exact_coins_for_coins_3_pair_entry",
                    "type_arguments": [
                        "0x1::aptos_coin::AptosCoin",
                        "0x881ac202b1f1e6ad4efcff7a1d0579411533f2502417a19211cfc49751ddb5f4::coin::MOJO",
                        "0xf22bede237a07e121b56d91a491eb7bcdfd1f5907926a9e58338f964a01b17fa::asset::USDT",
                        "0xf22bede237a07e121b56d91a491eb7bcdfd1f5907926a9e58338f964a01b17fa::asset::USDC"
                    ],
                    "arguments": [
                        "1000000",
                        "49329"
                    ],
                    "type": "entry_function_payload"
            }
        """.trimIndent()
        val signingInput = Aptos.SigningInput.newBuilder()
            .setChainId(1)
            .setExpirationTimestampSecs(3664390082)
            .setGasUnitPrice(100)
            .setMaxGasAmount(100011)
            .setSender("0x07968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f30")
            .setSequenceNumber(42)
            .setAnyEncoded(payloadJson)
            .setPrivateKey(key)
            .build()

        val result = AnySigner.sign(signingInput, CoinType.APTOS, Aptos.SigningOutput.parser())
        assertEquals(
            Numeric.cleanHexPrefix(Numeric.toHexString(result.rawTxn.toByteArray())),
            "07968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f302a000000000000000216fe2df00ea7dde4a63409201f7f4e536bde7bb7335526a35d05111e68aa322c0f416e696d6553776170506f6f6c563127737761705f65786163745f636f696e735f666f725f636f696e735f335f706169725f656e747279040700000000000000000000000000000000000000000000000000000000000000010a6170746f735f636f696e094170746f73436f696e0007881ac202b1f1e6ad4efcff7a1d0579411533f2502417a19211cfc49751ddb5f404636f696e044d4f4a4f0007f22bede237a07e121b56d91a491eb7bcdfd1f5907926a9e58338f964a01b17fa05617373657404555344540007f22bede237a07e121b56d91a491eb7bcdfd1f5907926a9e58338f964a01b17fa056173736574045553444300020840420f000000000008b1c0000000000000ab860100000000006400000000000000c2276ada0000000001"
        )
        assertEquals(
            Numeric.cleanHexPrefix(Numeric.toHexString(result.authenticator.signature.toByteArray())),
            "42cd67406e85afd1e948e7ad7f5f484fb4c60d82b267c6b6b28a92301e228b983206d2b87cd5487cf9acfb0effbd183ab90123570eb2e047cb152d337152210b"
        )
        assertEquals(
            Numeric.cleanHexPrefix(Numeric.toHexString(result.encoded.toByteArray())),
            "07968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f302a000000000000000216fe2df00ea7dde4a63409201f7f4e536bde7bb7335526a35d05111e68aa322c0f416e696d6553776170506f6f6c563127737761705f65786163745f636f696e735f666f725f636f696e735f335f706169725f656e747279040700000000000000000000000000000000000000000000000000000000000000010a6170746f735f636f696e094170746f73436f696e0007881ac202b1f1e6ad4efcff7a1d0579411533f2502417a19211cfc49751ddb5f404636f696e044d4f4a4f0007f22bede237a07e121b56d91a491eb7bcdfd1f5907926a9e58338f964a01b17fa05617373657404555344540007f22bede237a07e121b56d91a491eb7bcdfd1f5907926a9e58338f964a01b17fa056173736574045553444300020840420f000000000008b1c0000000000000ab860100000000006400000000000000c2276ada00000000010020ea526ba1710343d953461ff68641f1b7df5f23b9042ffa2d2a798d3adb3f3d6c4042cd67406e85afd1e948e7ad7f5f484fb4c60d82b267c6b6b28a92301e228b983206d2b87cd5487cf9acfb0effbd183ab90123570eb2e047cb152d337152210b"
        )
    }

    @Test
    fun AptosTransactionSigning() {
        // Successfully broadcasted https://explorer.aptoslabs.com/txn/0xb4d62afd3862116e060dd6ad9848ccb50c2bc177799819f1d29c059ae2042467?network=devnet
        val key =
            "5d996aa76b3212142792d9130796cd2e11e3c445a93118c08414df4f66bc60ec".toHexBytesInByteString()

        val transfer = Aptos.TransferMessage.newBuilder().setAmount(1000)
            .setTo("0x07968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f30").build()
        val signingInput = Aptos.SigningInput.newBuilder().setChainId(33)
            .setSender("0x07968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f30")
            .setSequenceNumber(99)
            .setGasUnitPrice(100)
            .setMaxGasAmount(3296766)
            .setExpirationTimestampSecs(3664390082)
            .setTransfer(transfer)
            .setPrivateKey(key)
            .build()

        val result = AnySigner.sign(signingInput, CoinType.APTOS, Aptos.SigningOutput.parser())
        assertEquals(
            Numeric.cleanHexPrefix(Numeric.toHexString(result.rawTxn.toByteArray())),
            "07968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f3063000000000000000200000000000000000000000000000000000000000000000000000000000000010d6170746f735f6163636f756e74087472616e7366657200022007968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f3008e803000000000000fe4d3200000000006400000000000000c2276ada0000000021"
        )
        assertEquals(
            Numeric.cleanHexPrefix(Numeric.toHexString(result.authenticator.signature.toByteArray())),
            "5707246db31e2335edc4316a7a656a11691d1d1647f6e864d1ab12f43428aaaf806cf02120d0b608cdd89c5c904af7b137432aacdd60cc53f9fad7bd33578e01"
        )
        assertEquals(
            Numeric.cleanHexPrefix(Numeric.toHexString(result.encoded.toByteArray())),
            "07968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f3063000000000000000200000000000000000000000000000000000000000000000000000000000000010d6170746f735f6163636f756e74087472616e7366657200022007968dab936c1bad187c60ce4082f307d030d780e91e694ae03aef16aba73f3008e803000000000000fe4d3200000000006400000000000000c2276ada00000000210020ea526ba1710343d953461ff68641f1b7df5f23b9042ffa2d2a798d3adb3f3d6c405707246db31e2335edc4316a7a656a11691d1d1647f6e864d1ab12f43428aaaf806cf02120d0b608cdd89c5c904af7b137432aacdd60cc53f9fad7bd33578e01"
        )
    }
}
