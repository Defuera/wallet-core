// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <PublicKey.h>
#include <string>
#include <regex>

namespace TW::Aeternity {

    static const std::string prefix = "ak_"; //todo should I use 'ak_'?

class Address {
  public:

    /// Determines whether a string makes a valid address.
    static bool isValid(const std::string& string);

    /// Initializes an address from a string representation.
    Address(const std::string& string);

    /// Initializes an address from a public key.
    Address(const PublicKey& publicKey);

    /// Returns a string representation of the Aeternity address.
    std::string string() const;

  private:
    static std::string assertedType(const std::string& data, const std::string& type);
    std::regex* regex;
};
} // namespace TW::Aeternity
