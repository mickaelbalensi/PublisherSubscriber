DELETE FROM Crypto WHERE ID = 4;

/* INSERT INTO Crypto (id_crypto, name_crypto, symbol_crypto) VALUES ("MIC", "MIC", "MIC");
 */
/* INSERT into Subscriptions (subscriber_id, crypto_id, [start_date])
VALUES (2, 3, '2024-08-29 12:17:02') */


/* INSERT INTO CryptoValues (crypto_id, [timestamp], basic_current_price,
    basic_market_cap, basic_total_volume, basic_price_change_percentage_24h,
    high_24h, low_24h, price_change_percentage_7d, price_change_percentage_30d,
    circulating_supply, total_supply, twitter_followers, reddit_subscribers,
    forks, stars, sentiment_votes_up_percentage, sentiment_votes_down_percentage)
VALUES (2, "2024-08-29 12:16:03", 2549.4, 306793078184, 17811628711, 3.2859, 2557.01,
    2461.86, -3.20771, -23.73989, 120298529.853779, 120298529.853779, 3460990, 0, 19618,
    44422, 80.85, 19.15);

INSERT INTO CryptoValues (crypto_id, [timestamp], basic_current_price,
    basic_market_cap, basic_total_volume, basic_price_change_percentage_24h,
    high_24h, low_24h, price_change_percentage_7d, price_change_percentage_30d,
    circulating_supply, total_supply, twitter_followers, reddit_subscribers,
    forks, stars, sentiment_votes_up_percentage, sentiment_votes_down_percentage)
VALUES  (3, "2024-08-29 12:16:03", 0.573049, 32203039654, 1221729155, -0.29746, 0.583924,
    0.557275, -4.5194, -4.37882, 56180094752.0, 99987315360.0, 2740127, 0, 1525, 4384,
    55.93, 44.07);

INSERT INTO CryptoValues (crypto_id, [timestamp], basic_current_price,
    basic_market_cap, basic_total_volume, basic_price_change_percentage_24h,
    high_24h, low_24h, price_change_percentage_7d, price_change_percentage_30d,
    circulating_supply, total_supply, twitter_followers, reddit_subscribers,
    forks, stars, sentiment_votes_up_percentage, sentiment_votes_down_percentage)
VALUES (1, "2024-08-29 12:20:01", 59637, 1177882920407, 33787519655, 0.65422, 60230,
    57968, -2.16809, -10.74534, 19746668.0, 21000000.0, 6812945, 0, 36426, 73168,
    77.1, 22.9);

INSERT INTO CryptoValues (crypto_id, [timestamp], basic_current_price,
    basic_market_cap, basic_total_volume, basic_price_change_percentage_24h,
    high_24h, low_24h, price_change_percentage_7d, price_change_percentage_30d,
    circulating_supply, total_supply, twitter_followers, reddit_subscribers,
    forks, stars, sentiment_votes_up_percentage, sentiment_votes_down_percentage)
VALUES (2, "2024-08-29 12:20:01", 2550.14, 306729376222, 17882079652, 3.22003, 2557.01,
    2461.86, -3.08026, -23.71794, 120298529.853779, 120298529.853779, 3460990, 0, 19618,
    44422, 80.85, 19.15);

INSERT INTO CryptoValues (crypto_id, [timestamp], basic_current_price,
    basic_market_cap, basic_total_volume, basic_price_change_percentage_24h,
    high_24h, low_24h, price_change_percentage_7d, price_change_percentage_30d,
    circulating_supply, total_supply, twitter_followers, reddit_subscribers,
    forks, stars, sentiment_votes_up_percentage, sentiment_votes_down_percentage)
VALUES  (3, "2024-08-29 12:20:01", 0.573054, 32292651919, 1227393791, -0.29658, 0.583924,
    0.557275, -4.51856, -4.37798, 56180094752.0, 99987315360.0, 2740127, 0, 1525, 4384,
    55.93, 44.07)  */











/*  insert data into Crypto
INSERT INTO Crypto (id_crypto, name_crypto, symbol_crypto) 
VALUES ('ethereum', 'Ethereum', 'eth');

INSERT INTO Crypto (id_crypto, name_crypto, symbol_crypto) 
VALUES ('bitcoin', 'Bitcoin', 'btc'); 

INSERT INTO Crypto (id_crypto, name_crypto, symbol_crypto)
VALUES ('ripple', 'XRP', 'xrp')
*/

/*  insert data into CryptoValues 

INSERT INTO CryptoValues (crypto_id, [timestamp], basic_current_price, 
        basic_market_cap, basic_total_volume, basic_price_change_percentage_24h,
         high_24h, low_24h, price_change_percentage_7d, price_change_percentage_30d,
          circulating_supply, total_supply, twitter_followers, reddit_subscribers, 
          forks, stars, sentiment_votes_up_percentage, sentiment_votes_down_percentage)
VALUES (1, '2024-08-29 12:01:02', 59543, 1175710181049, 36205280424, 0.47042, 60230,
     57968, -2.21933, -10.8681, 19746668.0, 21000000.0, 6812945, 0, 36426, 73168, 
     76.13, 23.87); 

INSERT INTO CryptoValues (crypto_id, [timestamp], basic_current_price,
        basic_market_cap, basic_total_volume, basic_price_change_percentage_24h,
         high_24h, low_24h, price_change_percentage_7d, price_change_percentage_30d,
          circulating_supply, total_supply, twitter_followers, reddit_subscribers, 
          forks, stars, sentiment_votes_up_percentage, sentiment_votes_down_percentage)

VALUES (2 , "2024-08-29 12:06:26", 2548.28, 306683053351, 17526248158, 3.47073, 2557.01,
     2461.86, -3.25057, -23.77365, 120298529.853779, 120298529.853779, 3460990, 0, 
     19618, 44422, 80.85, 19.15);

INSERT INTO CryptoValues (crypto_id, [timestamp], basic_current_price,
        basic_market_cap, basic_total_volume, basic_price_change_percentage_24h,
         high_24h, low_24h, price_change_percentage_7d, price_change_percentage_30d,
          circulating_supply, total_supply, twitter_followers, reddit_subscribers, 
          forks, stars, sentiment_votes_up_percentage, sentiment_votes_down_percentage)

VALUES (3 , "2024-08-29 12:01:02", 0.573123, 32194564716, 1193620971, -0.04139, 0.583924,
     0.557275, -4.60707, -4.36635, 56180094752.0, 99987315360.0, 2740127, 0, 1525,
     4384, 56.2, 43.8)
 */






 
/*  insert data into Subscribers
INSERT INTO Subscribers DEFAULT VALUES;
*/

/*  insert data into Subscriptions
INSERT INTO Subscriptions (subscriber_id, crypto_id, is_paid, [start_date])
 VALUES (1, 1, true, '2024-08-20 12:01:02');

INSERT INTO Subscriptions (subscriber_id, crypto_id, is_paid, [start_date])
 VALUES (1, 2, true, '2024-08-20 12:01:02');

INSERT INTO Subscriptions (subscriber_id, crypto_id, is_paid, [start_date])
 VALUES (2, 1, false, '2024-08-20 12:01:02'); 
*/



