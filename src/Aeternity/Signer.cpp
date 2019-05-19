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
    Data sigRawArray[64] = {
        Data(11),  Data(4),   Data(234), Data(63),  Data(226), Data(192), Data(156), Data(195),
        Data(74),  Data(163), Data(16),  Data(228), Data(171), Data(129), Data(110), Data(57),
        Data(15),  Data(11),  Data(86),  Data(215), Data(184), Data(18),  Data(54),  Data(46),
        Data(58),  Data(176), Data(167), Data(109), Data(107), Data(66),  Data(68),  Data(69),
        Data(70),  Data(254), Data(251), Data(189), Data(16),  Data(39),  Data(189), Data(233),
        Data(111), Data(159), Data(1),   Data(103), Data(1),   Data(227), Data(62),  Data(141),
        Data(103), Data(0),   Data(239), Data(105), Data(141), Data(131), Data(62),  Data(187),
        Data(112), Data(224), Data(81),  Data(241), Data(71),  Data(37),  Data(135), Data(2)};


    std::vector<uint8_t> myVector;
    append(myVector, )
    myVector.insert(0, 11);

    auto sigRaw = Data();
    for (int i = 0; i < 64; i++) {
        append(sigRaw, sigRawArray[i]);
    }

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
