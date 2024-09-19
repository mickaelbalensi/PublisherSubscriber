
SELECT 
    subscriber_id,
    crypto_id,
    name_crypto,
    symbol_crypto,
    timestamp,
    basic_current_price,
    basic_market_cap,
    basic_total_volume,
    basic_price_change_percentage_24h
FROM 
    free_subscriber_crypto_values
WHERE 
    subscriber_id = 1 


/* SELECT cv.*
FROM CryptoValues cv
JOIN Subscriptions s ON cv.crypto_id = s.crypto_id
JOIN Subscribers sub ON s.subscriber_id = sub.subscriber_id
WHERE sub.subscriber_id = 1
AND cv.timestamp >= datetime('now', '-7 days')
AND cv.timestamp <= datetime('now')
ORDER BY cv.timestamp DESC; */