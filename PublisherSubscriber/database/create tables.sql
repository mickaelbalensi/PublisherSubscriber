
CREATE TABLE Crypto (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    idcrypto TEXT NOT NULL,
    [name] TEXT NOT NULL,
    symbol TEXT NOT NULL,
    current_price REAL NOT NULL,
    market_cap INTEGER NOT NULL,
    total_volume INTEGER NOT NULL,
    price_change_percentage_24h REAL NOT NULL
); 

DROP TABLE ClassicCrypto;

CREATE TABLE PremiumCrypto (
    id INTEGER PRIMARY KEY,
    high_24h REAL NOT NULL,
    low_24h REAL NOT NULL,
    price_change_percentage_7d REAL NOT NULL,
    price_change_percentage_30d REAL NOT NULL,
    circulating_supply REAL NOT NULL,
    total_supply REAL NOT NULL,
    twitter_followers INTEGER NOT NULL,
    reddit_subscribers INTEGER NOT NULL,
    forks INTEGER NOT NULL,
    stars INTEGER NOT NULL,
    sentiment_votes_up_percentage REAL NOT NULL,
    sentiment_votes_down_percentage REAL NOT NULL,
    FOREIGN KEY(id) REFERENCES Crypto(id)
);

CREATE TABLE Subscribers (
    id INTEGER PRIMARY KEY,
    client_type TEXT NOT NULL CHECK(client_type IN ('classic', 'premium')),
    crypto_id INTEGER,
    FOREIGN KEY(crypto_id) REFERENCES ClassicCrypto(id)
);

/* 
-- struct ClassicCryptoInfo
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
}; */
