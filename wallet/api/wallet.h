//
// Created by Ngo Nghia on 2019-03-01.
//

#ifndef TEST_WALLET_H
#define TEST_WALLET_H

#include "wallet_api.h"
#include <string>
#include <crypto/crypto.h>

namespace Monero {

    class WalletImpl : public Wallet {
    public:
        WalletImpl(const std::string& mnemonic, NetworkType nettype = MAINNET);
        WalletImpl(const std::string& address, const std::string& secret_spend_key, const std::string& secret_view_key, NetworkType nettype = MAINNET);
        ~WalletImpl() override;
        std::string getSeed() const override;
        std::string getSeedLanguage() const override;
        std::string getAddress() const override;
        NetworkType getNettype() const override;

        /*!
         * \brief secretViewKey     - returns secret view key
         * \return                  - secret view key
         */
        std::string getSecretViewKey() const override;

        /*!
         * \brief publicViewKey     - returns public view key
         * \return                  - public view key
         */
        std::string getPublicViewKey() const override;

        /*!
         * \brief secretSpendKey    - returns secret spend key
         * \return                  - secret spend key
         */
        std::string getSecretSpendKey() const override;

        /*!
         * \brief publicSpendKey    - returns public spend key
         * \return                  - public spend key
         */
        std::string getPublicSpendKey() const override;

    private:
        std::string m_seed;
        crypto::secret_key m_secret_spend_key;
        crypto::secret_key m_secret_view_key;
        crypto::public_key m_public_spend_key;
        crypto::public_key m_public_view_key;
        std::string m_address;
        NetworkType m_nettype;
    };
}

#endif //TEST_WALLET_H
