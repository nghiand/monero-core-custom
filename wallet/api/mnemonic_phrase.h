//
// Created by Ngo Nghia on 2019-03-01.
//

#ifndef TEST_MNEMONIC_PHRASE_H
#define TEST_MNEMONIC_PHRASE_H

#include "wallet/api/wallet_api.h"
#include <string>

namespace Monero {

    class MnemonicPhraseImpl : public MnemonicPhrase {
    public:
        MnemonicPhraseImpl(const std::string& phrase);
        ~MnemonicPhraseImpl();

        std::string toSeed(const std::string& password);

    private:
        std::string phrase;
    };
}

#endif //TEST_MNEMONIC_PHRASE_H
