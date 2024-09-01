#include "cryptoFactory.hpp"

CryptoFactory::CryptoFactory() {
    Add(CLIENT_TYPE::CLASSIC, []() { return std::make_shared<ClassicCrypto>(); });
    Add(CLIENT_TYPE::PREMIUM, []() { return std::make_shared<PremiumCrypto>(); });
}

std::shared_ptr<ICrypto> CryptoFactory::Create(CLIENT_TYPE type) {
    return m_cryptos[type]();
}

void CryptoFactory::Add(CLIENT_TYPE type, std::function<std::shared_ptr<ICrypto>()> func) {
    m_cryptos[type] = func;
}
