#include "subscriber_shapes.hpp"

const size_t BUFFLEN = 1024;
Subscriber::Subscriber(std::shared_ptr<SHAPE[]> shapes, size_t len)
    : m_shapes(shapes), m_len(len), isWaiting(true) {
    m_server.WaitingRequest();
    Register();
}

Subscriber::~Subscriber() {
    isWaiting = false;
}

void Subscriber::Register() {

    char response[BUFFLEN];
    size_t offset = 0;
    
    *(size_t *)(response) = m_len;
    offset += sizeof(size_t);

    for (size_t i = 0; i < m_len; i++) 
    {
        *(SHAPE*)(response + offset) = m_shapes[i];
        offset += sizeof(SHAPE);
    }

    m_server.Acknowledge(response, offset);
    std::thread t1([&] { WaitEvent(); });
    t1.detach();
}

void Subscriber::WaitEvent() {
    ShapeFactory fact;
    while (isWaiting) {
        std::shared_ptr<uint8_t[]> message = m_server.WaitingRequest();

        auto *shapeHeader = reinterpret_cast<ShapeHeader*>(message.get());
        SHAPE shapeType = static_cast<SHAPE>(ntohl(static_cast<uint32_t>(shapeHeader->shape)));

        std::shared_ptr<IShape> shape = fact.CreateShape(shapeType);
        shape->Deserialize(message);
        shape->print();
    }
}
