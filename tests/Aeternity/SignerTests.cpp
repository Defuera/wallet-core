// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Aeternity/Signer.h"
#include "Aeternity/Transaction.h"
#include "HexCoding.h"

#include <Aeternity/Address.h>
#include <gtest/gtest.h>

using namespace TW;
using namespace TW::Aeternity;

TEST(AeternitySigner, Sign) {
    std::string sender_id = "ak_2a1j2Mk9YSmC1gioUq4PWRm3bsv887MbuRVwyv4KaUGoR1eiKi";
    std::string recipient_id = "ak_Egp9yVdpxmvAfQ7vsXGvpnyfNq71msbdUpkMNYGTeTe8kPL3v";
    uint64_t amount = 10;
    double fee = 2e13;
    std::string payload = "Hello World";
    uint64_t ttl = 82757;
    uint64_t nonce = 49;

    auto transaction = Transaction(sender_id, recipient_id, amount, fee, payload, ttl, nonce);
    auto privateKey = PrivateKey(parse_hex("4646464646464646464646464646464646464646464646464646464646464646"));

    auto signature = Signer::sign(privateKey, transaction);

    EXPECT_EQ(signature, "sg_CwTqP+LAnMNKoxDkq4FuOQ8LVte4EjYuOrCnbWtCREUw+WMqapVGiL9V6CO9F93gcIt9YNehmYdmcB3XJ9pSAYnrNz4=");
}

