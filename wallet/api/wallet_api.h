//
// Created by Ngo Nghia on 2019-03-01.
//

#ifndef TEST_WALLET_API_H
#define TEST_WALLET_API_H

#include <cstdint>
#include <string>

namespace Monero {

    enum NetworkType : uint8_t {
        MAINNET = 0,
        TESTNET,
        STAGENET
    };

    struct MnemonicPhrase {
        virtual std::string toSeed(const std::string &password) = 0;
    };

    struct Wallet {
        virtual ~Wallet() = 0;
        virtual std::string getSeed() const = 0;
        virtual std::string getSeedLanguage() const = 0;
        virtual std::string getAddress() const = 0;
        virtual NetworkType getNettype() const = 0;
        bool mainnet() const { return getNettype() == MAINNET; }
        bool testnet() const { return getNettype() == TESTNET; }
        bool stagenet() const { return getNettype() == STAGENET; }

        /*!
         * \brief secretViewKey     - returns secret view key
         * \return                  - secret view key
         */
        virtual std::string getSecretViewKey() const = 0;

        /*!
         * \brief publicViewKey     - returns public view key
         * \return                  - public view key
         */
        virtual std::string getPublicViewKey() const = 0;

        /*!
         * \brief secretSpendKey    - returns secret spend key
         * \return                  - secret spend key
         */
        virtual std::string getSecretSpendKey() const = 0;

        /*!
         * \brief publicSpendKey    - returns public spend key
         * \return                  - public spend key
         */
        virtual std::string getPublicSpendKey() const = 0;

    };

}

namespace Bitmonero = Monero;

#endif //TEST_WALLET_API_H
