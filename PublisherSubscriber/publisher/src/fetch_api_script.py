import asyncio
import aiohttp
import time
import json
import os
import sys
from datetime import datetime

BASE_URL = "https://api.coingecko.com/api/v3"

async def fetch(session, url):
    async with session.get(url) as response:
        return await response.json()

async def get_coin_data(session, coin_id):
    url = f"{BASE_URL}/coins/{coin_id}?localization=false&tickers=false&market_data=true&community_data=true&developer_data=true&sparkline=false"
    return await fetch(session, url)

def process_classic_data(data):
    return {
        "id": data["id"],
        "name": data["name"],
        "symbol": data["symbol"],
        "current_price": data["market_data"]["current_price"]["usd"],
        "market_cap": data["market_data"]["market_cap"]["usd"],
        "total_volume": data["market_data"]["total_volume"]["usd"],
        "price_change_percentage_24h": data["market_data"]["price_change_percentage_24h"],
    }

def process_premium_data(data):
    classic_data = process_classic_data(data)
    premium_data = {
        "high_24h": data["market_data"]["high_24h"]["usd"],
        "low_24h": data["market_data"]["low_24h"]["usd"],
        "price_change_percentage_7d": data["market_data"]["price_change_percentage_7d"],
        "price_change_percentage_30d": data["market_data"]["price_change_percentage_30d"],
        "circulating_supply": data["market_data"]["circulating_supply"],
        "total_supply": data["market_data"]["total_supply"],
        "twitter_followers": data["community_data"]["twitter_followers"],
        "reddit_subscribers": data["community_data"]["reddit_subscribers"],
        "forks": data["developer_data"]["forks"],
        "stars": data["developer_data"]["stars"],
        "sentiment_votes_up_percentage": data["sentiment_votes_up_percentage"],
        "sentiment_votes_down_percentage": data["sentiment_votes_down_percentage"],
    }
    return {**classic_data, **premium_data}

async def get_coins_data(coin_ids):
    async with aiohttp.ClientSession() as session:
        tasks = [get_coin_data(session, coin_id) for coin_id in coin_ids]
        return await asyncio.gather(*tasks)

def save_to_json2(data, filename):
    with open(filename, 'w') as f:
        json.dump(data, f, indent=2)

def save_to_json3(data, base_filename):
    i = 1
    filename = f'data/{base_filename}{i}.json'
    while os.path.exists(filename):
        i += 1
        filename = f'data/{base_filename}{i}.json'
    with open(filename, 'w') as f:
        json.dump(data, f, indent=2)

def save_to_json(data, base_filename):
    timestamp = datetime.now().strftime('%d-%m-%H-%M-%S')
    filename = f'data/{base_filename}_{timestamp}.json'
    with open(filename, 'w') as f:
        json.dump(data, f, indent=2)

async def main():
    print("Debug: Entering main function", file=sys.stderr)
    coin_ids = ["bitcoin", "ethereum", "ripple"]
    start_time = time.time()
    
    print(f"Debug: About to fetch data for {coin_ids}", file=sys.stderr)
    try:
        coins_data = await get_coins_data(coin_ids)
        
        print("Debug: Data fetched, processing...", file=sys.stderr)
        classic_data = [process_classic_data(coin) for coin in coins_data]
        premium_data = [process_premium_data(coin) for coin in coins_data]
        
        print("Debug: Creating data directory", file=sys.stderr)
        os.makedirs('data', exist_ok=True)

        print("Debug: Saving data to JSON files", file=sys.stderr)
        save_to_json(classic_data, 'classic_data')
        save_to_json(premium_data, 'premium_data')
        
        print(f"Debug: Execution time: {time.time() - start_time:.2f} seconds", file=sys.stderr)
        print("Debug: Data saved", file=sys.stderr)
    except Exception as e:
        print(f"Error in main function: {str(e)}", file=sys.stderr)

def run_main():
    print("Debug: Starting run_main()", file=sys.stderr)
    try:
        loop = asyncio.get_event_loop()
        loop.run_until_complete(main())
    except Exception as e:
        print(f"Error in run_main: {str(e)}", file=sys.stderr)
    finally:
        print("Debug: Finished run_main()", file=sys.stderr)

run_main()
