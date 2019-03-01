//
// Created by Ngo Nghia on 2019-03-01.
//

#include "wallet.h"
#include "string_tools.h"
#include "mnemonic_phrase.h"
#include "wallet_errors.h"
#include "cryptonote_basic/account.h"
#include <cstdio>
#include <iostream>

namespace Monero {

    WalletImpl::WalletImpl(const std::string &mnemonic, NetworkType nettype) {
        MnemonicPhraseImpl mnemonicPhrase = MnemonicPhraseImpl(mnemonic);
        this->m_seed = mnemonicPhrase.toSeed("");
        this->m_nettype = nettype;

        crypto::secret_key seed;
        epee::string_tools::hex_to_pod(this->m_seed, seed);


        cryptonote::account_base account{};

        account.generate(seed, true, false, false);

        this->m_secret_view_key = account.get_keys().m_view_secret_key;
        this->m_secret_spend_key = account.get_keys().m_spend_secret_key;
        this->m_public_view_key = account.get_keys().m_account_address.m_view_public_key;
        this->m_public_spend_key = account.get_keys().m_account_address.m_spend_public_key;
        this->m_address = account.get_public_address_str(static_cast<cryptonote::network_type>(nettype));
    }

    WalletImpl::WalletImpl(const std::string &address, const std::string &secret_spend_key,
                           const std::string &secret_view_key, NetworkType nettype) {
        this->m_seed = secret_spend_key;
        this->m_address = address;

        cryptonote::address_parse_info decoded_address_info;

        THROW_WALLET_EXCEPTION_IF(
                !cryptonote::get_account_address_from_str(
                        decoded_address_info,
                        static_cast<cryptonote::network_type>(nettype),
                        address
                ),
                tools::error::wallet_internal_error,
                "Invalid spend key");
        THROW_WALLET_EXCEPTION_IF(decoded_address_info.is_subaddress, tools::error::wallet_internal_error,
                                  "Sub-address is not supported");
        THROW_WALLET_EXCEPTION_IF(!epee::string_tools::hex_to_pod(secret_spend_key, this->m_secret_spend_key),
                                  tools::error::wallet_internal_error, "Invalid spend key");
        THROW_WALLET_EXCEPTION_IF(!epee::string_tools::hex_to_pod(secret_view_key, this->m_secret_view_key),
                                  tools::error::wallet_internal_error, "Invalid view key");

        THROW_WALLET_EXCEPTION_IF(!crypto::secret_key_to_public_key(this->m_secret_view_key, this->m_public_view_key),
                                  tools::error::wallet_internal_error, "Invalid view key");
        THROW_WALLET_EXCEPTION_IF(!crypto::secret_key_to_public_key(this->m_secret_spend_key, this->m_public_spend_key),
                                  tools::error::wallet_internal_error, "Invalid spend key");
        this->m_nettype = nettype;
    }

    Wallet::~Wallet() {

    }

    WalletImpl::~WalletImpl() {

    }

    std::string WalletImpl::getSeed() const {
        return this->m_seed;
    }

    std::string WalletImpl::getSeedLanguage() const {
        return "English";
    }

    std::string WalletImpl::getAddress() const {
        return this->m_address;
    }

    NetworkType WalletImpl::getNettype() const {
        return this->m_nettype;
    }

    std::string WalletImpl::getSecretViewKey() const {
        return epee::string_tools::pod_to_hex(this->m_secret_view_key);
    }

    std::string WalletImpl::getPublicViewKey() const {
        return epee::string_tools::pod_to_hex(this->m_public_view_key);
    }

    std::string WalletImpl::getSecretSpendKey() const {
        return epee::string_tools::pod_to_hex(this->m_secret_spend_key);
    }

    std::string WalletImpl::getPublicSpendKey() const {
        return epee::string_tools::pod_to_hex(this->m_public_spend_key);
    }

}
