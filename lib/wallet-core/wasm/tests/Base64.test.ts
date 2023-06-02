// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

import { assert } from "chai";
import { Buffer } from "buffer";

describe("Base64", () => {

  it("test decoding", () => {
    const { Base64 } = globalThis.core;

    const decoded = Base64.decode("SGVsbG9Xb3JsZA==");

    assert.equal(Buffer.from(decoded).toString(), "HelloWorld");
  });

  it("test encoding", () => {
    const { Base64 } = globalThis.core;

    const encoded = Base64.encode(Buffer.from("HelloWorld"));

    assert.equal(encoded, "SGVsbG9Xb3JsZA==");
  });

  it("test encoding (URL-safe)", () => {
    const { Base64 } = globalThis.core;

    const encoded = Base64.encodeUrl(Buffer.from("==?="));

    assert.equal(encoded, "PT0_PQ==");
  });

  it("test decoding (URL-safe)", () => {
    const { Base64 } = globalThis.core;
    const decoded = Base64.decodeUrl("PT0_PQ==");

    assert.equal(Buffer.from(decoded).toString(), "==?=");
  });
});
