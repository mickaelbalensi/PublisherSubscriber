
CREATE VIEW All_Subscriber_Crypto_values AS
SELECT s.subscriber_id,
       s.is_paid,
       c.id as crypto_id,
       c.name_crypto,
       c.symbol_crypto,
       cv.timestamp,
       cv.basic_current_price,
       cv.basic_market_cap,
       cv.basic_total_volume,
       cv.basic_price_change_percentage_24h,
       cv.high_24h,
       cv.low_24h,
       cv.price_change_percentage_7d,
       cv.price_change_percentage_30d,
       cv.circulating_supply,
       cv.total_supply,
       cv.twitter_followers,
       cv.reddit_subscribers,
       cv.forks,
       cv.stars,
       cv.sentiment_votes_down_percentage,
       cv.sentiment_votes_up_percentage

FROM Subscribers s
INNER JOIN Subscriptions subs ON s.subscriber_id = subs.subscriber_id 
INNER JOIN Crypto c ON subs.crypto_id = c.id
INNER JOIN CryptoValues cv ON c.id = cv.crypto_id

WHERE cv.timestamp > s.created_at
    AND cv.timestamp > subs.start_date