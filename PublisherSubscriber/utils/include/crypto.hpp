#ifndef CRYPTO_INFO_HPP
#define CRYPTO_INFO_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <arpa/inet.h>
#include "json.hpp" // JSON library
using json = nlohmann::json;

enum class CLIENT_TYPE : uint32_t
{
    CLASSIC = 0,
    PREMIUM = 1
};

class ISerializer
{
public:
    virtual ~ISerializer() = default;

    virtual std::shared_ptr<uint8_t[]> Serialize() = 0;
    virtual void Deserialize(const std::shared_ptr<uint8_t[]>& buffer) = 0;

    virtual uint64_t GetSerializedSize() const = 0;
};

#pragma pack(push, 1)
struct CryptoHeader
{
    uint32_t magic;     // Magic number for type safety
    uint32_t version;   // For future versioning
    CLIENT_TYPE client_type;
};

struct ClassicCryptoInfo
{
    uint8_t m_id[32];
    uint8_t m_name[32];
    uint8_t m_symbol[8];
    double m_current_price;
    uint64_t m_market_cap;
    uint64_t m_total_volume;
    double m_price_change_percentage_24h;
    ClassicCryptoInfo() = default;
    explicit ClassicCryptoInfo(const json& data);
};

struct PremiumCryptoInfo
{
    double m_high_24h;
    double m_low_24h;
    double m_price_change_percentage_7d;
    double m_price_change_percentage_30d;
    double m_circulating_supply;
    double m_total_supply;
    uint32_t m_twitter_followers;
    uint32_t m_reddit_subscribers;
    uint32_t m_forks;
    uint32_t m_stars;
    double m_sentiment_votes_up_percentage;
    double m_sentiment_votes_down_percentage;
    PremiumCryptoInfo() = default;
    explicit PremiumCryptoInfo(const json& data);
};
#pragma pack(pop)

class ICrypto : private ISerializer
{
public:
    explicit ICrypto(CLIENT_TYPE client_type);
    virtual ~ICrypto() = default;

    std::shared_ptr<uint8_t[]> Serialize() override = 0;
    void Deserialize(const std::shared_ptr<uint8_t[]>& buffer) override = 0;
    virtual void print() const = 0;

    uint64_t GetSerializedSize() const override = 0;
    CLIENT_TYPE GetClientType() const { return m_header.client_type; }

protected:
    CryptoHeader m_header;

private:
    static const uint32_t MAGIC = 0x43525950;  // "CRYP" in ASCII
    static const uint32_t VERSION = 1;
};

class ClassicCrypto : public ICrypto
{
public:
    explicit ClassicCrypto();
    explicit ClassicCrypto(const json& data);

    std::shared_ptr<uint8_t[]> Serialize() override;
    void Deserialize(const std::shared_ptr<uint8_t[]>& buffer) override;
    void print() const override;

    uint64_t GetSerializedSize() const override;

    /* void SetData(const std::string& id, const std::string& name, const std::string& symbol,
                 double current_price, uint64_t market_cap, uint64_t total_volume,
                 float price_change_percentage_24h);
 */
protected:
    ClassicCryptoInfo m_info;
};

class PremiumCrypto : public ClassicCrypto
{
public:
    explicit PremiumCrypto();
    explicit PremiumCrypto(const json& data);

    std::shared_ptr<uint8_t[]> Serialize() override;
    void Deserialize(const std::shared_ptr<uint8_t[]>& buffer) override;
    void print() const override;

    uint64_t GetSerializedSize() const override;

    /* void SetAdditionalData(double high_24h, double low_24h, uint32_t circulating_supply,
                           uint32_t total_supply, uint32_t max_supply, uint32_t ath,
                           const std::string& ath_date, float ath_change_percentage);
 */
private:
    PremiumCryptoInfo m_premium_info;
};

#endif // CRYPTO_INFO_HPP