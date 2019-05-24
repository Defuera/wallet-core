// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Signer.h"
#include "Address.h"
#include "Base64.h"
#include "ChecksumEncoder.h"
#include "HexCoding.h"
#include "Identifiers.h"
#include <Data.h>
#include <Ethereum/RLP.h>

using namespace TW;
using namespace Aeternity;

/// implementation copied from
/// https://github.com/aeternity/aepp-sdk-go/blob/07aa8a77e5/aeternity/helpers.go#L367
std::string Aeternity::Signer::sign(const TW::PrivateKey &privateKey, Transaction &transaction) {
    auto txRaw = parseRawTransaction(transaction.encode());

    /// append networkId and txRaw
    auto data = Data();
    std::vector<byte> bytes(Identifiers::networkId.begin(), Identifiers::networkId.end());
    append(data, bytes);
    append(data, txRaw);

    /// sign ed25519
    auto sigRaw = privateKey.sign(data, TWCurveED25519); // todo is different, then go sdk -/
    auto signature = ChecksumEncoder::encode(Identifiers::prefixSignature, sigRaw);

    return signature;
}

Data TW::Aeternity::Signer::parseRawTransaction(const std::string &transaction) {
    auto trimPrefix =
        transaction.substr(Identifiers::prefixTransaction.size(), transaction.size() - 1);
    auto txWithChecksum = TW::Base64::decode(trimPrefix);

    /// trimChecksum
    auto start = txWithChecksum.begin();
    auto end = txWithChecksum.end() - ChecksumEncoder::checkSumSize;
    Data txRaw(start, end);
    return txRaw;
}
