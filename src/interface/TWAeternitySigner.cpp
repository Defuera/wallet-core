// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../Aeternity/Address.h"
#include "../Aeternity/Signer.h"
#include "../Aeternity/Transaction.h"
#include "../proto/Aeternity.pb.h"
#include "../uint256.h"
#include <TrustWalletCore/TWAeternitySigner.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace TW;
using namespace TW::Aeternity;

TW_Aeternity_Proto_SigningOutput TWAeternitySignerSign(TW_Aeternity_Proto_SigningInput data) {
    Proto::SigningInput input;
    input.ParseFromArray(TWDataBytes(data), static_cast<int>(TWDataSize(data)));

    auto privateKey = PrivateKey(Data(input.private_key().begin(), input.private_key().end()));

    auto from = Address(input.from_address());
    auto to = Address(input.to_address());

    std::string sender_id = "ak_2p5878zbFhxnrm7meL7TmqwtvBaqcBddyp5eGzZbovZ5FeVfcw";
    std::string recipient_id = "ak_Egp9yVdpxmvAfQ7vsXGvpnyfNq71msbdUpkMNYGTeTe8kPL3v";
    uint64_t amount = 10;
    double fee = 2e13;
    std::string payload = "Hello World";
    uint64_t ttl = 82757;
    uint64_t nonce = 49;

    auto tx = Transaction(sender_id, recipient_id, amount, fee, payload, ttl, nonce);

//    auto tx = Transaction(
//       from,
//       to,
//       input.amount(),
//       input.fee(),
//       input.payload(),
//       input.ttl(),
//       input.nonce()
//    );

    auto output = Signer::sign(privateKey, tx);

    auto serialized = output.SerializeAsString();
    return TWDataCreateWithBytes(reinterpret_cast<const uint8_t *>(serialized.data()), serialized.size());
}
