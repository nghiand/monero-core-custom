//
// Created by Ngo Nghia on 2019-03-01.
//

#include "mnemonic_phrase.h"
#include "mnemonics/electrum-words.h"
#include "string_tools.h"
#include <iostream>
#include <cstdio>

namespace Monero {

    MnemonicPhraseImpl::MnemonicPhraseImpl(const std::string &phrase) {
        this->phrase = phrase;
    }

    MnemonicPhraseImpl::~MnemonicPhraseImpl() {}

    std::string MnemonicPhraseImpl::toSeed(const std::string &password) {
        if (this->phrase.empty()) {
            return "";
        }

        std::string normalized_mnemonic = std::string(this->phrase);
        std::replace(normalized_mnemonic.begin(), normalized_mnemonic.end(), '\r', ' ');
        std::replace(normalized_mnemonic.begin(), normalized_mnemonic.end(), '\n', ' ');
        std::replace(normalized_mnemonic.begin(), normalized_mnemonic.end(), '\t', ' ');

        const epee::wipeable_string &mnemonic_wipeable = normalized_mnemonic;
        crypto::secret_key secret_seed;
        std::string mnemonic_language;

        if (!crypto::ElectrumWords::words_to_bytes(mnemonic_wipeable, secret_seed, mnemonic_language)) {
            return "";
        }
        std::string secret_seed_string = epee::string_tools::pod_to_hex(secret_seed);

        return secret_seed_string;
    }
}