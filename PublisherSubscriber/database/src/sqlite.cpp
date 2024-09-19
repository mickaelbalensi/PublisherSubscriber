#include "sqlite.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

SQLite::SQLite(const char *path)
{
    int rc;
    // Open database
    rc = sqlite3_open(path, &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error(std::string("Can't open database: ") +
                                                             sqlite3_errmsg(db));
    }
}

SQLite::~SQLite()
{
    sqlite3_close(db);
}

void SQLite::Insert(const CryptoTable &crypto)
{
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Crypto (id_crypto, name_crypto, symbol_crypto) VALUES (?, ?, ?)";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, crypto.id, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, crypto.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, crypto.symbol, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }

    sqlite3_finalize(stmt);
}

void SQLite::Insert(const CryptoValuesTable &values)
{
    const char *sql = "INSERT INTO CryptoValues (crypto_id, [timestamp], \
                    basic_current_price, basic_market_cap, basic_total_volume, \
                    basic_price_change_percentage_24h, high_24h, low_24h, \
                    price_change_percentage_7d, price_change_percentage_30d, \
                    circulating_supply, total_supply, twitter_followers, \
                    reddit_subscribers, forks, stars, sentiment_votes_up_percentage, \
                    sentiment_votes_down_percentage) \
                    VALUES (?, datetime(?, 'unixepoch'), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) 
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    int64_t timestamp_seconds = std::chrono::duration_cast<std::chrono::seconds>(values.timestamp.time_since_epoch()).count();

    sqlite3_bind_int64(stmt, 1, 5);
    sqlite3_bind_int64(stmt, 2, timestamp_seconds);
    sqlite3_bind_double(stmt, 3, values.current_price);
    sqlite3_bind_double(stmt, 4, values.market_cap);
    sqlite3_bind_double(stmt, 5, values.total_volume);
    sqlite3_bind_double(stmt, 6, values.price_change_percentage_24h);
    sqlite3_bind_double(stmt, 7, values.m_high_24h);
    sqlite3_bind_double(stmt, 8, values.m_low_24h);
    sqlite3_bind_double(stmt, 9, values.m_price_change_percentage_7d);
    sqlite3_bind_double(stmt, 10, values.m_price_change_percentage_30d);
    sqlite3_bind_double(stmt, 11, values.m_circulating_supply);
    sqlite3_bind_double(stmt, 12, values.m_total_supply);
    sqlite3_bind_int(stmt, 13, values.m_twitter_followers);
    sqlite3_bind_int(stmt, 14, values.m_reddit_subscribers);
    sqlite3_bind_int(stmt, 15, values.m_forks);
    sqlite3_bind_int(stmt, 16, values.m_stars);
    sqlite3_bind_double(stmt, 17, values.m_sentiment_votes_up_percentage);
    sqlite3_bind_double(stmt, 18, values.m_sentiment_votes_down_percentage);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }

    sqlite3_finalize(stmt);
}

void SQLite::Insert(const SubscriberTable &subscriber)
{
    const char *sql = "INSERT INTO Subscribers (created_at, is_paid) VALUES (datetime(?, 'unixepoch'), ?)";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    int64_t timestamp_seconds = std::chrono::duration_cast<std::chrono::seconds>(subscriber.created_at.time_since_epoch()).count();

    sqlite3_bind_int64(stmt, 1, timestamp_seconds);
    sqlite3_bind_int(stmt, 2, subscriber.is_paid);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }

    sqlite3_finalize(stmt);
}

void SQLite::Insert(const SubscriptionTable &subscription)
{
    const char *sql = "INSERT INTO Subscriptions (crypto_id, subscriber_id, start_date) VALUES (?, ?, datetime(?, 'unixepoch'))";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Convert nanoseconds to seconds for the timestamp
    int64_t timestamp_seconds = std::chrono::duration_cast<std::chrono::seconds>(subscription.created_at.time_since_epoch()).count();

    sqlite3_bind_int64(stmt, 1, subscription.id_crypto);
    sqlite3_bind_int64(stmt, 2, subscription.id_subscriber);
    sqlite3_bind_int64(stmt, 3, timestamp_seconds);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }

    sqlite3_finalize(stmt);
}

std::chrono::system_clock::time_point parseTimestamp(const char* timestampStr) {
    // Step 1: Parse the string into std::tm
    std::tm tm = {};
    std::istringstream ss(timestampStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");  // Parse string to tm structure
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse timestamp");
    }

    // Step 2: Convert std::tm to time_t (seconds since epoch)
    std::time_t timeT = std::mktime(&tm);

    // Step 3: Convert time_t to std::chrono::system_clock::time_point
    return std::chrono::system_clock::from_time_t(timeT);
}

int callback(void* data, int argc, char** argv, char** colName) {
    std::vector<HistoryTable>* records = static_cast<std::vector<HistoryTable>*>(data);
    
    HistoryTable record;
    record.subscriber_id = std::stoi(argv[0]);
    record.crypto_id = std::stoi(argv[2]);
    strcpy(record.name_crypto, argv[3]);
    strcpy(record.symbole_crypto, argv[4]);
    record.timestamp = parseTimestamp(argv[5]);
    record.current_price = std::stod(argv[6]);
    record.market_cap = std::stoull(argv[7]);
    record.total_volume = std::stoull(argv[8]);
    record.price_change_percentage_24h = std::stof(argv[9]);
    
    records->push_back(record);
    return 0;
}

HistoryTable SQLite::SelectFreeHistory(uint32_t sub_id, size_t fromDays)
{
    std::vector<HistoryTable> records;
    std::string sql = "SELECT * FROM All_Subscriber_Crypto_values WHERE subscriber_id = "
            + std::to_string(sub_id) + " AND timestamp > datetime('now', '-"
            + std::to_string(fromDays) + " days')";
    
    std::cout << sql << std::endl;

    char *errMsg = nullptr;
    int exit = sqlite3_exec(db, sql.c_str(), callback, &records, &errMsg);

    if (exit != SQLITE_OK) {
        sqlite3_free(errMsg);
        throw std::runtime_error("Failed to select records");
    }
    else
    {
        std::cout << "Query executed successfully!" << std::endl;
        std::cout << "Records returned: " << records.size() << std::endl;
        
        for (const auto& record : records) {\
            static int i = 0;

            std::cout << "Record " << ++i << ":" << std::endl;
            std::cout << "subscriber_id " << record.subscriber_id << std::endl;
            std::cout << "crypto_id " << record.crypto_id << std::endl;
            std::cout << "name_crypto " << record.name_crypto << std::endl;
            std::cout << "symbole_crypto " << record.symbole_crypto << std::endl;
            std::time_t time = std::chrono::system_clock::to_time_t(record.timestamp);
            std::cout << "timestamp " << std::ctime(&time);
            std::cout << "current_price " << record.current_price << std::endl;
            std::cout << "market_cap " << record.market_cap << std::endl;
            std::cout << "total_volume " << record.total_volume << std::endl;
            std::cout << "price_change_percentage_24h " << record.price_change_percentage_24h << std::endl;
            std::cout << std::endl;
        }
    }





    return HistoryTable();
}
PremiumHistoryTable SQLite::SelectPremiumHistory(uint32_t sub_id, size_t fromDays)
{
    return PremiumHistoryTable();
}
/* void SQLite::Insert(const CryptoTable &crypto)
{
    char* errMsg = nullptr;
    std::string sql = "INSERT INTO Crypto (id_crypto, name_crypto, symbol_crypto) VALUES (\"";
    sql += crypto.id;
    sql += "\", \"";
    sql += crypto.name;
    sql += "\", \"";
    sql += crypto.symbol;
    sql += "\")";
    std::cout << sql << std::endl;

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }
}
 */
/* void SQLite::Insert(const CryptoValuesTable &values)
{
    char* errMsg = nullptr;
    std::string sql = "INSERT INTO CryptoValues (crypto_id, [timestamp], \
                    basic_current_price, basic_market_cap, basic_total_volume, \
                    basic_price_change_percentage_24h,high_24h, low_24h, \
                    price_change_percentage_7d, price_change_percentage_30d,\
                    circulating_supply, total_supply, twitter_followers, \
                    reddit_subscribers,forks, stars, sentiment_votes_up_percentage, \
                    sentiment_votes_down_percentage) VALUES (";

    sql += values.id_crypto;
    sql += ", ";
    sql += std::to_string(values.timestamp.time_since_epoch().count());
    sql += ", ";
    sql += std::to_string(values.current_price);
    sql += ", ";
    sql += std::to_string(values.market_cap);
    sql += ", ";
    sql += std::to_string(values.total_volume);
    sql += ", ";
    sql += std::to_string(values.price_change_percentage_24h);
    sql += ", ";
    sql += std::to_string(values.m_high_24h);
    sql += ", ";
    sql += std::to_string(values.m_low_24h);
    sql += ", ";
    sql += std::to_string(values.m_price_change_percentage_7d);
    sql += ", ";
    sql += std::to_string(values.m_price_change_percentage_30d);
    sql += ", ";
    sql += std::to_string(values.m_circulating_supply);
    sql += ", ";
    sql += std::to_string(values.m_total_supply);
    sql += ", ";
    sql += std::to_string(values.m_twitter_followers);
    sql += ", ";
    sql += std::to_string(values.m_reddit_subscribers);
    sql += ", ";
    sql += std::to_string(values.m_forks);
    sql += ", ";
    sql += std::to_string(values.m_stars);
    sql += ", ";
    sql += std::to_string(values.m_sentiment_votes_up_percentage);
    sql += ", ";
    sql += std::to_string(values.m_sentiment_votes_down_percentage);
    sql += ");";

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }
}

void SQLite::Insert(const SubscriberTable &subscriber)
{
    char* errMsg = nullptr;
    std::string sql = "INSERT INTO Subscriber (created_at, is_paid) VALUES (";
    sql += std::to_string(subscriber.created_at.time_since_epoch().count());
    sql += ", ";
    sql += std::to_string(subscriber.is_paid);
    sql += ");";
}

void SQLite::Insert(const SubscriptionTable &subscription)
{
    char* errMsg = nullptr;
    std::string sql = "INSERT INTO Subscription (crypto_id, subscriber_id, \
                        created_at) VALUES (";
    sql += std::to_string(subscription.id_crypto);
    sql += ", ";
    sql += std::to_string(subscription.id_subscriber);
    sql += ", ";
    sql += std::to_string(subscription.created_at.time_since_epoch().count());
    sql += ");";

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }
}



 */