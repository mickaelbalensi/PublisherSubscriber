#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "cryptoFactory.hpp"
#include "crypto.hpp"
#include "server.hpp"
#include <thread>
#include <chrono>
#include <memory>

class Subscriber
{
public:
    explicit Subscriber(CLIENT_TYPE type);
    ~Subscriber();

private:
    void Register();
    void WaitEvent();

    UDPServer m_server;
    CLIENT_TYPE m_type;
    bool isWaiting;
};

#endif // SUBSCRIBER_HPP
