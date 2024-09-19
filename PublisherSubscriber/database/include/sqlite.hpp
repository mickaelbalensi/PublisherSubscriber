#ifndef SQLITE_HPP
#define SQLITE_HPP
#include <chrono>
#include <sqlite3.h>

struct CryptoTable 
{
    const char *id;
    const char *name;
    const char *symbol;
};

struct CryptoValuesTable
{
    const char *id_crypto;
    std::chrono::system_clock::time_point timestamp;
    double current_price;
    size_t market_cap;
    size_t total_volume;
    float price_change_percentage_24h;
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
};

struct SubscriberTable
{
std::chrono::system_clock::time_point created_at;
bool is_paid;
};

struct SubscriptionTable
{
uint32_t id_crypto;
uint32_t id_subscriber;
std::chrono::system_clock::time_point created_at;
};

struct HistoryTable
{
    uint32_t subscriber_id;
    uint32_t crypto_id;
    char name_crypto[15];
    char symbole_crypto[4];
    std::chrono::system_clock::time_point timestamp;
    double current_price;
    size_t market_cap;
    size_t total_volume;
    float price_change_percentage_24h;
};

struct PremiumHistoryTable : public HistoryTable
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
};


class SQLite {
public:
    explicit SQLite(const char* path);
    ~SQLite();
    void Insert(const CryptoTable& crypto);
    void Insert(const CryptoValuesTable& values);
    void Insert(const SubscriberTable& subscriber);
    void Insert(const SubscriptionTable& subscription);
    HistoryTable SelectFreeHistory(uint32_t sub_id, size_t fromDays);
    PremiumHistoryTable SelectPremiumHistory(uint32_t sub_id, size_t fromDays);
private:
    sqlite3* db;
};






#endif // SQLITE_HPP