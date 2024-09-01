#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>

class CryptoCurrency {
public:
    std::string id;
    std::string name;
    std::string symbol;
    double current_price;
    double market_cap;
    double total_volume;
    double price_change_percentage_24h;
    double high_24h;
    double low_24h;
    double price_change_percentage_7d;
    double price_change_percentage_30d;
    double circulating_supply;
    double total_supply;
    int twitter_followers;
    int reddit_subscribers;
    int forks;
    int stars;
    double sentiment_votes_up_percentage;
    double sentiment_votes_down_percentage;

    // Constructor
    CryptoCurrency(/* Initialize with data from JSON */) {}
};

class PremiumService {
public:
    static double calculateRSI(const std::vector<double>& prices, int period = 14) {
        if (prices.size() < period + 1) {
            return 0;
        }

        std::vector<double> changes(prices.size() - 1);
        for (size_t i = 1; i < prices.size(); ++i) {
            changes[i-1] = prices[i] - prices[i-1];
        }

        double avg_gain = 0, avg_loss = 0;
        for (int i = 0; i < period; ++i) {
            if (changes[i] > 0) avg_gain += changes[i];
            else avg_loss -= changes[i];
        }
        avg_gain /= period;
        avg_loss /= period;

        double rs = avg_gain / avg_loss;
        return 100.0 - (100.0 / (1.0 + rs));
    }

    static double calculateSupplyRatio(const CryptoCurrency& crypto) {
        return (crypto.circulating_supply / crypto.total_supply) * 100.0;
    }

    static double calculateLiquidityRatio(const CryptoCurrency& crypto) {
        return (crypto.total_volume / crypto.market_cap) * 100.0;
    }

    static double calculateSentimentScore(const CryptoCurrency& crypto) {
        return crypto.sentiment_votes_up_percentage - crypto.sentiment_votes_down_percentage;
    }

    static double calculateDeveloperActivityScore(const CryptoCurrency& crypto) {
        return (crypto.forks + crypto.stars) / 1000.0;  // Normalize to a 0-100 scale
    }

    static void generatePremiumReport(const CryptoCurrency& crypto) {
        std::cout << "Premium Report for " << crypto.name << " (" << crypto.symbol << ")\n";
        std::cout << "Current Price: $" << crypto.current_price << "\n";
        std::cout << "24h Change: " << crypto.price_change_percentage_24h << "%\n";
        std::cout << "7d Change: " << crypto.price_change_percentage_7d << "%\n";
        std::cout << "30d Change: " << crypto.price_change_percentage_30d << "%\n";
        std::cout << "Supply Ratio: " << calculateSupplyRatio(crypto) << "%\n";
        std::cout << "Liquidity Ratio: " << calculateLiquidityRatio(crypto) << "%\n";
        std::cout << "Sentiment Score: " << calculateSentimentScore(crypto) << "\n";
        std::cout << "Developer Activity Score: " << calculateDeveloperActivityScore(crypto) << "\n";
    }

    static void checkMultiCriteriaAlert(const CryptoCurrency& crypto, double priceChangeThreshold, double sentimentThreshold) {
        if (crypto.price_change_percentage_24h > priceChangeThreshold && 
            calculateSentimentScore(crypto) > sentimentThreshold) {
            std::cout << "ALERT: " << crypto.name << " has increased by " << crypto.price_change_percentage_24h 
                      << "% in the last 24h and has a positive sentiment score of " << calculateSentimentScore(crypto) << "\n";
        }
    }
};

int main() {
    // Example usage
    CryptoCurrency bitcoin(/* Initialize with data from JSON */);
    
    PremiumService::generatePremiumReport(bitcoin);
    PremiumService::checkMultiCriteriaAlert(bitcoin, 5.0, 50.0);

    return 0;
}