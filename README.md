# Cryptocurrency Data Distribution

A multi-process/multi-threading project implementing a publisher-subscriber design pattern for cryptocurrency data distribution.

## Project Overview

This project implements a publisher-subscriber system for distributing cryptocurrency data. Subscribers can register to receive information about various cryptocurrencies, with two subscription tiers available: classic and premium. The system uses UDP for inter-process communication and stores data in an SQLite database.

### Key Features

- Two subscription tiers: Classic and Premium
- Real-time cryptocurrency data from CoinGecko API
- Data storage in SQLite database
- UDP-based networking between processes
- SQL query capability for subscribers to retrieve historical data
- Multi-process and multi-threading architecture

## Data Examples

### Classic Subscription

```json
{
  "id": "bitcoin",
  "name": "Bitcoin",
  "symbol": "btc",
  "current_price": 59543,
  "market_cap": 1175710181049,
  "total_volume": 36205280424,
  "price_change_percentage_24h": 0.47042
}
```

### Premium Subscription

```json
{
  "id": "bitcoin",
  "name": "Bitcoin",
  "symbol": "btc",
  "current_price": 59543,
  "market_cap": 1175710181049,
  "total_volume": 36205280424,
  "price_change_percentage_24h": 0.47042,
  "high_24h": 60230,
  "low_24h": 57968,
  "price_change_percentage_7d": -2.21933,
  "price_change_percentage_30d": -10.8681,
  "circulating_supply": 19746668.0,
  "total_supply": 21000000.0,
  "twitter_followers": 6812945,
  "reddit_subscribers": 0,
  "forks": 36426,
  "stars": 73168,
  "sentiment_votes_up_percentage": 76.13,
  "sentiment_votes_down_percentage": 23.87
}
```



## Building the Project

To build the project, use the provided makefile:

```
make
```

## Usage

To run the publisher process:
```
make run-publisher
```

To run a subscriber process:
```
make run-subscriber ARGS="1"  # For classic subscription
make run-subscriber ARGS="2"  # For premium subscription
```

## Dependencies

- SQLite
