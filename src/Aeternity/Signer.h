// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Transaction.h"
#include <PrivateKey.h>

static std::string networkId = "ae_mainnet"; // todo can I hardcode this one?

namespace TW::Aeternity {

class Signer {
  public:
    /// Signs the given transaction.
    static std::string sign(const PrivateKey &privateKey, Transaction &transaction);

    static std::string encode(std::string basicString, const Data &vector);

    static Data parseRawTransaction(std::string transaction);

  private:
};

} // namespace TW::Aeternity
