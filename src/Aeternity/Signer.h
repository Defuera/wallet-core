// Copyright © 2017-2019 Trust.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Transaction.h"
#include <PrivateKey.h>

namespace TW::Aeternity {

class Signer {
  public:
    /// Signs the given transaction.
    static std::string sign(const PrivateKey &privateKey, Transaction &transaction);

    static Data parseRawTransaction(const std::string &transaction);
};

} // namespace TW::Aeternity
