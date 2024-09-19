#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "cryptoFactory.hpp"
#include "crypto.hpp"
#include "server.hpp"
#include <thread>
#include <chrono>
#include <memory>

using uid_t = uint32_t;
class Subscriber
{
public:
    explicit Subscriber(CLIENT_TYPE type);
    ~Subscriber();
    void History(size_t fromDay);
    void Pause();
    void Resume();

private:
    void Register();
    void WaitEvent();

    UDPServer m_server;
    CLIENT_TYPE m_type;
    bool isWaiting;
    const uid_t m_id;
};

#endif // SUBSCRIBER_HPP
