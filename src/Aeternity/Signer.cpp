// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Signer.h"
#include "Base64.h"
#include "HexCoding.h"
#include <Data.h>
#include <Ethereum/RLP.h>

using namespace TW;
using namespace Aeternity;

// SignEncodeTx
std::string Aeternity::Signer::sign(const TW::PrivateKey &privateKey, Transaction &transaction) {
    std::string txPrefix = "tx_";
    auto encodedTx = transaction.encode();
    auto trimPrefix = encodedTx.substr(txPrefix.size(), encodedTx.size() - 1);
    auto txRaw = TW::Base64::decode(trimPrefix); // parse_hex(trimPrefix);

    /// append networkId and txRaw
    auto data = Data();
    std::vector<byte> bytes(networkId.begin(), networkId.end());
    append(data, bytes);
    append(data, txRaw);

    /// sign
    /// ed25519.Sign(account.SigningKey, data)
        auto sigRaw = privateKey.sign(data, TWCurveED25519); //todo is different, then go sdk -/

    /// encode the message using rlp
    auto objectTagSignedTransaction = 11;
    auto rlpMessageVersion = 1; // todo same as Tx

    auto rlpTxRaw = Data();
    append(rlpTxRaw, Ethereum::RLP::encode(objectTagSignedTransaction));
    append(rlpTxRaw, Ethereum::RLP::encode(rlpMessageVersion));
    append(rlpTxRaw, Ethereum::RLP::encode(sigRaw));
    append(rlpTxRaw, Ethereum::RLP::encode(txRaw));

    /// encode the rlp message with the prefix
    auto signedEncodedTx = encode("tx_", rlpTxRaw); // PrefixTransaction

    /// compute the hash, calculate the blacke2b 32bit hash of the input byte array
    auto rlpTxHashRaw = Hash::blake2b(rlpTxRaw, 32);

    auto signedEncodedTxHash =
        encode("th_", rlpTxHashRaw); // PrefixTransactionHash = HashPrefix("th_")

    auto signature = encode("sg_", sigRaw); // PrefixSignature

    return signature;
}

// Encode a byte array into base58 with chacksum and a prefix
std::string TW::Aeternity::Signer::encode(const std::string prefix,
                                          const TW::Data &rawTx) { // todo copy from Tx
    std::vector<unsigned char> arrayOfByte(4);
    auto checksum = Hash::sha256(Hash::sha256(rawTx));
    std::copy(std::begin(checksum), std::end(checksum), std::begin(arrayOfByte));

    auto data = Data();
    append(data, rawTx);
    append(data, arrayOfByte);

    return prefix + TW::Base64::encode(data);
}
