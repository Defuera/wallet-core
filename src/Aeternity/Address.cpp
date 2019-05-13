// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Address.h"
#include <Base58.h>
#include <HexCoding.h>

using namespace TW::Aeternity;

/// Determines whether a string makes a valid address.
/// copied from \see https://github.com/aeternity/aepp-sdk-js/blob/develop/es/utils/crypto.js
bool TW::Aeternity::Address::isValid(const std::string &string) {
    const std::string &type = assertedType(string, prefix);
    unsigned long base58 = Base58::bitcoin.decodeCheck(type).size();
    return base58 == 32;
}

/// Initializes an address from a string representation.
TW::Aeternity::Address::Address(const std::string &string) {
    // 1 base58
    //    auto encoded = Base58::bitcoin.encodeCheck(string);
    //
    //    // 2 concatenate with prefix
    //    auto address = prefix + encoded;
}

/// Initializes an address from a public key.
TW::Aeternity::Address::Address(const PublicKey &publicKey) {
    if (publicKey.type != TWPublicKeyTypeED25519) {
        throw std::invalid_argument("Invalid public key type");
    }

    // todo

    //    auto publicKeyData = publicKey.bytes;
    //
    //    auto pkdata = Data(publicKeyData.begin(), publicKeyData.end());
    //    pkdata.insert(pkdata.begin(), 0x21);
    //    pkdata.push_back(0xAC);
    //
    //    auto keyHash = Hash::ripemd(Hash::sha256(pkdata));
    //    keyHash.insert(keyHash.begin(), 0x17);

    //    if (keyHash.size() != Address::size)
    //        throw std::invalid_argument("Invalid address key data");
    //
    //    std::copy(keyHash.data(), keyHash.data() + Address::size, bytes.begin());
}

/// Returns a string representation of the Bravo address.
std::string Address::string() const {
    return ""; // prefix + Base58::bitcoin.encodeCheck("");
}

std::string Address::assertedType(const std::string &data, const std::string &type) {
    try {

        const std::basic_regex base_regex("^${ak\\_}_.+ $");
        std::smatch base_match;

        if (std::regex_match(data, base_regex)) {

            int n = data.length();
            char charBuffer[n + 1];
            strcpy(charBuffer, data.c_str());

            char *token = strtok(charBuffer, "_");
            return token;
        } else {
            return nullptr;
        }
    } catch (const std::exception &e) {
        printf(e.what());
        return nullptr;
    }
}
