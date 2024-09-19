#include "../include/crypto.hpp"

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <iomanip>

const char* BLUEPRINT = "\033[0;34m";
const char* GREENPRINT = "\033[0;32m";
const char* WHITEPRINT = "\033[0;37m";

double htond(double x);
double ntohd(double x);
float htonf(float x);
float ntohf(float x);

ClassicCryptoInfo::ClassicCryptoInfo(const json& data)
{
    std::memcpy(m_id, data[0]["id"].get<std::string>().c_str(), 32);
    std::memcpy(m_name, data[0]["name"].get<std::string>().c_str(), 32);
    std::memcpy(m_symbol, data[0]["symbol"].get<std::string>().c_str(), 8);
    m_current_price = data[0]["current_price"].get<double>();
    m_market_cap = data[0]["market_cap"].get<uint64_t>();
    m_total_volume = data[0]["total_volume"].get<uint64_t>();
    m_price_change_percentage_24h = data[0]["price_change_percentage_24h"].get<double>();
}

PremiumCryptoInfo::PremiumCryptoInfo(const json& data)
{
    m_high_24h = data[0]["high_24h"].get<double>();
    m_low_24h = data[0]["low_24h"].get<double>();
    m_price_change_percentage_7d = data[0]["price_change_percentage_7d"].get<double>();
    m_price_change_percentage_30d = data[0]["price_change_percentage_30d"].get<double>();
    m_circulating_supply = data[0]["circulating_supply"].get<double>();
    m_total_supply = data[0]["total_supply"].get<double>();
    m_twitter_followers = data[0]["twitter_followers"].get<uint32_t>();
    m_reddit_subscribers = data[0]["reddit_subscribers"].get<uint32_t>();
    m_forks = data[0]["forks"].get<uint32_t>();
    m_stars = data[0]["stars"].get<uint32_t>();
    m_sentiment_votes_up_percentage = data[0]["sentiment_votes_up_percentage"].get<double>();
    m_sentiment_votes_down_percentage = data[0]["sentiment_votes_down_percentage"].get<double>();
}

ICrypto::ICrypto(CLIENT_TYPE client_type)
    : m_header{MAGIC, VERSION, client_type} {}

ClassicCrypto::ClassicCrypto()
    : ICrypto(CLIENT_TYPE::CLASSIC) {}

ClassicCrypto::ClassicCrypto(const json& data)
    : ICrypto(CLIENT_TYPE::CLASSIC), m_info(data) {}

PremiumCrypto::PremiumCrypto()
{
    m_header.client_type = CLIENT_TYPE::PREMIUM;
}

PremiumCrypto::PremiumCrypto(const json& data)
    : ClassicCrypto(data), m_premium_info(data) 
{
    m_header.client_type = CLIENT_TYPE::PREMIUM;
}

std::shared_ptr<uint8_t[]> ICrypto::Serialize() 
{
    std::shared_ptr<uint8_t[]> buffer(new uint8_t[GetSerializedSize()]);
    CryptoHeader* header = reinterpret_cast<CryptoHeader*>(buffer.get());
    header->magic = htonl(m_header.magic);
    header->version = htonl(m_header.version);
    header->client_type = static_cast<CLIENT_TYPE>(htonl(static_cast<uint32_t>(m_header.client_type)));
    return buffer;
}

void ICrypto::Deserialize(const std::shared_ptr<uint8_t[]>& buffer)
{
    if (!buffer) {
        throw std::runtime_error("NULL Buffer for deserialization");
    }

    CryptoHeader* header = reinterpret_cast<CryptoHeader*>(buffer.get());

    m_header.magic = ntohl(header->magic);
    if (m_header.magic != MAGIC) {
        throw std::runtime_error("Invalid magic number in buffer");
    }

    m_header.version = ntohl(header->version);
    if (m_header.version != VERSION) {
        throw std::runtime_error("Unsupported version number");
    }

    //m_header.client_type = static_cast<CLIENT_TYPE>(ntohl(static_cast<uint32_t>(header->client_type)));
} 

uint64_t ICrypto::GetSerializedSize() const {
    return sizeof(CryptoHeader);
}

void ICrypto::print() const {
    if (m_header.client_type == CLIENT_TYPE::CLASSIC) 
        std::cout << GREENPRINT;
    else if (m_header.client_type == CLIENT_TYPE::PREMIUM)
        std::cout << BLUEPRINT;
}

std::shared_ptr<uint8_t[]> ClassicCrypto::Serialize() {
    auto buffer = ICrypto::Serialize();
    ClassicCryptoInfo* info = reinterpret_cast<ClassicCryptoInfo*>(buffer.get() + ICrypto::GetSerializedSize());

    std::memcpy(info->m_id, m_info.m_id, sizeof(m_info.m_id));
    std::memcpy(info->m_name, m_info.m_name, sizeof(m_info.m_name));
    std::memcpy(info->m_symbol, m_info.m_symbol, sizeof(m_info.m_symbol));
    
    info->m_current_price = htond(m_info.m_current_price);
    info->m_market_cap = htobe64(m_info.m_market_cap);
    info->m_total_volume = htobe64(m_info.m_total_volume);
    info->m_price_change_percentage_24h = htond(m_info.m_price_change_percentage_24h);

    return buffer;
}

void ClassicCrypto::Deserialize(const std::shared_ptr<uint8_t[]>& buffer) {
    ICrypto::Deserialize(buffer);

    const auto* info = reinterpret_cast<const ClassicCryptoInfo*>(buffer.get() + ICrypto::GetSerializedSize());

    std::memcpy(m_info.m_id, info->m_id, sizeof(m_info.m_id));
    std::memcpy(m_info.m_name, info->m_name, sizeof(m_info.m_name));
    std::memcpy(m_info.m_symbol, info->m_symbol, sizeof(m_info.m_symbol));
    
    m_info.m_current_price = ntohd(info->m_current_price);
    m_info.m_market_cap = be64toh(info->m_market_cap);
    m_info.m_total_volume = be64toh(info->m_total_volume);
    m_info.m_price_change_percentage_24h = ntohd(info->m_price_change_percentage_24h);
}

size_t ClassicCrypto::GetSerializedSize() const {
    return ICrypto::GetSerializedSize() + sizeof(ClassicCryptoInfo);
}

void ClassicCrypto::print() const {
    std::cout << "**************************************" << std::endl;

    ICrypto::print();

    std::cout << "Client Type: Classic\n";
    std::cout << "ID: " << m_info.m_id << "\n";
    std::cout << "Name: " << m_info.m_name << "\n";
    std::cout << "Symbol: " << m_info.m_symbol << "\n";
    std::cout << "Current Price: $" << std::fixed << std::setprecision(2) << m_info.m_current_price << "\n";
    std::cout << "Market Cap: $" << m_info.m_market_cap << "\n";
    std::cout << "Total Volume: $" << m_info.m_total_volume << "\n";
    std::cout << "Price Change (24h): " << std::setprecision(2) << m_info.m_price_change_percentage_24h << "%\n";
    std::cout << WHITEPRINT;
    std::cout << "**************************************" << std::endl;
}

/* void ClassicCrypto::SetData(const std::string& id, const std::string& name, const std::string& symbol,
                            double current_price, uint64_t market_cap, uint64_t total_volume,
                            float price_change_percentage_24h) {
    strncpy(m_info.id, id.c_str(), sizeof(m_info.id) - 1);
    strncpy(m_info.name, name.c_str(), sizeof(m_info.name) - 1);
    strncpy(m_info.symbol, symbol.c_str(), sizeof(m_info.symbol) - 1);
    m_info.current_price = current_price;
    m_info.market_cap = market_cap;
    m_info.total_volume = total_volume;
    m_info.price_change_percentage_24h = price_change_percentage_24h;
} */

std::shared_ptr<uint8_t[]> PremiumCrypto::Serialize() {
    std::shared_ptr<uint8_t[]> buffer(ClassicCrypto::Serialize());
    auto* info = reinterpret_cast<PremiumCryptoInfo*>(buffer.get() + ClassicCrypto::GetSerializedSize());

    info->m_high_24h = htond(m_premium_info.m_high_24h);
    info->m_low_24h = htond(m_premium_info.m_low_24h);
    info->m_price_change_percentage_7d = htond(m_premium_info.m_price_change_percentage_7d);
    info->m_price_change_percentage_30d = htond(m_premium_info.m_price_change_percentage_30d);
    info->m_circulating_supply = htond(m_premium_info.m_circulating_supply);
    info->m_total_supply = htond(m_premium_info.m_total_supply);
    info->m_twitter_followers = htonl(m_premium_info.m_twitter_followers);
    info->m_reddit_subscribers = htonl(m_premium_info.m_reddit_subscribers);
    info->m_forks = htonl(m_premium_info.m_forks);
    info->m_stars = htonl(m_premium_info.m_stars);
    info->m_sentiment_votes_up_percentage = htond(m_premium_info.m_sentiment_votes_up_percentage);
    info->m_sentiment_votes_down_percentage = htond(m_premium_info.m_sentiment_votes_down_percentage);

    return buffer;
}

void PremiumCrypto::Deserialize(const std::shared_ptr<uint8_t[]>& buffer) {
    ClassicCrypto::Deserialize(buffer);    

    const auto* info = reinterpret_cast<const PremiumCryptoInfo*>(buffer.get() + ClassicCrypto::GetSerializedSize());
    
    m_premium_info.m_high_24h = ntohd(info->m_high_24h);
    m_premium_info.m_low_24h = ntohd(info->m_low_24h);
    m_premium_info.m_price_change_percentage_7d = ntohd(info->m_price_change_percentage_7d);
    m_premium_info.m_price_change_percentage_30d = ntohd(info->m_price_change_percentage_30d);
    m_premium_info.m_circulating_supply = ntohd(info->m_circulating_supply);
    m_premium_info.m_total_supply = ntohd(info->m_total_supply);
    m_premium_info.m_twitter_followers = ntohl(info->m_twitter_followers);
    m_premium_info.m_reddit_subscribers = ntohl(info->m_reddit_subscribers);
    m_premium_info.m_forks = ntohl(info->m_forks);
    m_premium_info.m_stars = ntohl(info->m_stars);
    m_premium_info.m_sentiment_votes_up_percentage = ntohd(info->m_sentiment_votes_up_percentage);
    m_premium_info.m_sentiment_votes_down_percentage = ntohd(info->m_sentiment_votes_down_percentage);
}

size_t PremiumCrypto::GetSerializedSize() const {
    return ClassicCrypto::GetSerializedSize() + sizeof(PremiumCryptoInfo);
}

void PremiumCrypto::print() const {
    ClassicCrypto::print();

    std::cout << BLUEPRINT;
    std::cout << "Premium Client Additional Info:\n";
    std::cout << "High 24h: $" << std::fixed << std::setprecision(2) << m_premium_info.m_high_24h << "\n";
    std::cout << "Low 24h: $" << m_premium_info.m_low_24h << "\n";
    std::cout << "Price Change (7d): " << std::setprecision(2) << m_premium_info.m_price_change_percentage_7d << "%\n";
    std::cout << "Price Change (30d): " << m_premium_info.m_price_change_percentage_30d << "%\n";
    std::cout << "Circulating Supply: " << m_premium_info.m_circulating_supply << "\n";
    std::cout << "Total Supply: " << m_premium_info.m_total_supply << "\n";
    std::cout << "Twitter Followers: " << m_premium_info.m_twitter_followers << "\n";
    std::cout << "Reddit Subscribers: " << m_premium_info.m_reddit_subscribers << "\n";
    std::cout << "Forks: " << m_premium_info.m_forks << "\n";
    std::cout << "Stars: " << m_premium_info.m_stars << "\n";
    std::cout << "Sentiment Votes Up: " << m_premium_info.m_sentiment_votes_up_percentage << "%\n";
    std::cout << "Sentiment Votes Down: " << m_premium_info.m_sentiment_votes_down_percentage << "%\n";
    std::cout << WHITEPRINT;
    std::cout << "**************************************" << std::endl;
}
/* void PremiumCrypto::SetAdditionalData(double high_24h, double low_24h, float price_change_percentage_7d,
                                      float price_change_percentage_30d, double circulating_supply,
                                      double total_supply, uint32_t twitter_followers, uint32_t reddit_subscribers,
                                      uint32_t forks, uint32_t stars, float sentiment_votes_up_percentage,
                                      float sentiment_votes_down_percentage) {
    m_premium_info.high_24h = high_24h;
    m_premium_info.low_24h = low_24h;
    m_premium_info.price_change_percentage_7d = price_change_percentage_7d;
    m_premium_info.price_change_percentage_30d = price_change_percentage_30d;
    m_premium_info.circulating_supply = circulating_supply;
    m_premium_info.total_supply = total_supply;
    m_premium_info.twitter_followers = twitter_followers;
    m_premium_info.reddit_subscribers = reddit_subscribers;
    m_premium_info.forks = forks;
    m_premium_info.stars = stars;
    m_premium_info.sentiment_votes_up_percentage = sentiment_votes_up_percentage;
    m_premium_info.sentiment_votes_down_percentage = sentiment_votes_down_percentage;
}
 */

// Helper functions for double and float network byte order conversion
double htond(double x) {
    uint64_t tmp;
    memcpy(&tmp, &x, sizeof(tmp));
    tmp = htobe64(tmp);
    memcpy(&x, &tmp, sizeof(tmp));
    return x;
}


double ntohd(double x) {
    uint64_t tmp;
    memcpy(&tmp, &x, sizeof(tmp));
    tmp = be64toh(tmp);
    memcpy(&x, &tmp, sizeof(tmp));
    return x;
}

float htonf(float x) {
    uint32_t tmp;
    memcpy(&tmp, &x, sizeof(tmp));
    tmp = htonl(tmp);
    memcpy(&x, &tmp, sizeof(tmp));
    return x;
}

float ntohf(float x) {
    uint32_t tmp;
    memcpy(&tmp, &x, sizeof(tmp));
    tmp = ntohl(tmp);
    memcpy(&x, &tmp, sizeof(tmp));
    return x;
}