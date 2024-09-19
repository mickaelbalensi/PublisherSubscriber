#include <iostream>
#include "sqlite.hpp"

void TestInsertCrypto()
{
    std::cout << "TestInsertCrypto" << std::endl;
    SQLite db("crypto.db");
    CryptoTable crypto{"MIC", "MIC", "MIC"};
    db.Insert(crypto);
}

void TestInsertValues()
{
    std::cout << "TestInsertValues" << std::endl;
    CryptoValuesTable values{"MIC", std::chrono::system_clock::now(), 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    SQLite db("crypto.db");
    db.Insert(values);
}

void TestInsertSubscriber()
{
    std::cout << "TestInsertSubscriber" << std::endl;
    SubscriberTable subscriber{std::chrono::system_clock::now(), true};
    SQLite db("crypto.db");
    db.Insert(subscriber);
}

void TestInsertSubscribtion()
{
    std::cout << "TestInsertSubscribtion" << std::endl;
    SubscriptionTable subscribtion{5, 3, std::chrono::system_clock::now()};
    SQLite db("crypto.db");
    db.Insert(subscribtion);
}

void TestSelectFreeHistory()
{
    std::cout << "TestSelectFreeHistory" << std::endl;
    SQLite db("crypto.db");

    HistoryTable history = db.SelectFreeHistory(1, 30);

}


int main()
{
    /*
    TestInsertCrypto();
    TestInsertValues();
    TestInsertSubscriber();
    TestInsertSubscribtion();
    */
TestSelectFreeHistory();
    /*
    */
    return 0;
}