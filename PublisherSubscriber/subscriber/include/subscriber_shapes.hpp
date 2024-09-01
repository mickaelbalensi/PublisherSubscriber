#ifndef SUBSCRIBER_SHAPES_HPP
#define SUBSCRIBER_SHAPES_HPP

#include "../../utils/include/shapes.hpp"
#include "../../utils/include/shapeFactory.hpp"
#include "../../utils/include/server.hpp"
#include <thread>
#include <chrono>
#include <memory>

class Subscriber
{
public:
    explicit Subscriber(std::shared_ptr<SHAPE[]> shapes, size_t len);
    ~Subscriber();

private:
    void Register();
    void WaitEvent();

    UDPServer m_server;
    std::shared_ptr<SHAPE[]> m_shapes;
    size_t m_len;
    bool isWaiting;
};

#endif // SUBSCRIBER_SHAPES_HPP
