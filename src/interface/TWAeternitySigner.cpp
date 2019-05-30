// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../Aeternity/Signer.h"
#include "../Aeternity/Transaction.h"
#include "../proto/Aeternity.pb.h"
#include <TrustWalletCore/TWAeternitySigner.h>

using namespace TW;
using namespace TW::Aeternity;

TW_Aeternity_Proto_SigningOutput TWAeternitySignerSign(TW_Aeternity_Proto_SigningInput data) {
    Proto::SigningInput input;
    input.ParseFromArray(TWDataBytes(data), static_cast<int>(TWDataSize(data)));

    auto privateKey = PrivateKey(Data(input.private_key().begin(), input.private_key().end()));

    auto tx = Transaction(
        input.from_address(),
        input.to_address(),
        input.amount(),
        input.fee(),
        input.payload(),
        input.ttl(),
        input.nonce()
    );

    auto output = Signer::sign(privateKey, tx);

    auto serialized = output.SerializeAsString();
    return TWDataCreateWithBytes(reinterpret_cast<const uint8_t *>(serialized.data()), serialized.size());
}
