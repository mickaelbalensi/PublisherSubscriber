#ifndef CRYPTO_FACTORY
#define CRYPTO_FACTORY

#include <unordered_map>  // unordered_map
#include <memory>         // shared_ptr
#include <functional>     // std::function
#include "crypto.hpp"

class CryptoFactory
{
public:
    explicit CryptoFactory();

    std::shared_ptr<ICrypto> Create(CLIENT_TYPE type);

private:
    void Add(CLIENT_TYPE type, std::function<std::shared_ptr<ICrypto>()> func);

    std::unordered_map<CLIENT_TYPE, std::function<std::shared_ptr<ICrypto>()>> m_cryptos;
};

#endif // CRYPTO_FACTORY
