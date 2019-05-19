// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Transaction.h"
#include "Base64.h"
#include <Base58.h>
#include <Ethereum/RLP.h>
#include <Hash.h>

/// RLP returns a byte serialized representation
std::string TW::Aeternity::Transaction::encode() {
    uint objectTagSpendTransaction = 12;
    uint rlpMessageVersion = 1;

    auto encoded = Data();
    append(encoded, Ethereum::RLP::encode(objectTagSpendTransaction));
    append(encoded, Ethereum::RLP::encode(rlpMessageVersion));
    append(encoded, Ethereum::RLP::encode(buildTag(sender_id)));
    append(encoded, Ethereum::RLP::encode(buildTag(recipient_id)));
    append(encoded, Ethereum::RLP::encode(amount));
    append(encoded, Ethereum::RLP::encode(fee));
    append(encoded, Ethereum::RLP::encode(ttl));
    append(encoded, Ethereum::RLP::encode(nonce));
    append(encoded, Ethereum::RLP::encode(payload));

    const Data &raw = Ethereum::RLP::encodeList(encoded);
    auto tx = TW::Base64::encode(raw);
    auto result = finalize(txPrefix, raw);

    return result;
}

//// buildIDTag assemble an id() object
//// see https://github.com/aeternity/protocol/blob/epoch-v0.22.0/serializations.md#the-id-type
TW::Data TW::Aeternity::Transaction::buildTag(std::string &address) {
    auto payload = address.substr(txPrefix.size(), address.size()); // todo this is a wrong prefix

    auto data = Data();
    append(data, {0x1}); // todo have to use accountType
    append(data, Base58::bitcoin.decodeCheck(payload));

    return data;
}

std::vector<unsigned char> TW::Aeternity::Transaction::intToBytes(int paramInt) {
    std::vector<unsigned char> arrayOfByte(4);
    for (int i = 0; i < 4; i++)
        arrayOfByte[3 - i] = (paramInt >> (i * 8));
    return arrayOfByte;
}

// Encode a byte array into base58 with chacksum and a prefix
std::string TW::Aeternity::Transaction::finalize(const std::string prefix, const TW::Data &rawTx) {
    std::vector<unsigned char> arrayOfByte(4);
    auto checksum = Hash::sha256(Hash::sha256(rawTx));
    std::copy(std::begin(checksum), std::end(checksum), std::begin(arrayOfByte));


    auto data = Data();
    append(data, rawTx);
    append(data, arrayOfByte);

    return prefix + TW::Base64::encode(data);
}