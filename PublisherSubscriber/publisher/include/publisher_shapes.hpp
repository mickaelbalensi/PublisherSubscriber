#ifndef PUBLISHER
#define PUBLISHER
#include <unordered_map>
#include <vector>
#include <thread>
#include <memory>
#include <chrono>
#include "../../utils/include/client.hpp"
#include "../../utils/include/shapes.hpp"

using namespace std;

const std::chrono::seconds PERIOD_BROADCAST = 5s;

class Publisher
{
public:
    explicit Publisher();

    void EndBroadcast();
    void Publish(SHAPE shape, std::shared_ptr<IShape> shapePtr);
private:
    void StartBroadcast();
    void Subscribe();
    
    bool m_isBroadcasting;
    std::unordered_map<SHAPE, std::vector<sockaddr_in>> m_subscribers;
    UDPClientBroadcast m_udpClientBroadcast;
};

#endif