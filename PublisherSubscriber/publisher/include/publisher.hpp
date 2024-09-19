#ifndef PUBLISHER
#define PUBLISHER
#include <unordered_map>
#include <vector>
#include <thread>
#include <memory>
#include <chrono>
#include "client.hpp"
#include "crypto.hpp"

using namespace std;

const std::chrono::seconds PERIOD_BROADCAST = 5s;
using uid_t = uint32_t;
class Publisher
{
public:
    explicit Publisher();

    void EndBroadcast();
    void Publish(std::shared_ptr<ICrypto> shapePtr);
private:
    void StartBroadcast();
    void Subscribe();
    
    bool m_isBroadcasting;
    //std::vector<sockaddr_in> m_subscribers;
    std::unordered_map<uid_t,sockaddr_in> m_subscribers;
    uid_t m_totalSubscribers;
    UDPClientBroadcast m_udpClientBroadcast;
};

#endif