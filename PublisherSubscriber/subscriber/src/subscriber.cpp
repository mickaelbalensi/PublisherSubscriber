#include "subscriber.hpp"
const size_t BUFFLEN = 1024;
Subscriber::Subscriber(CLIENT_TYPE type)
    : m_type(type), isWaiting(true) {
    m_server.WaitingRequest();
    Register();
}

Subscriber::~Subscriber() {
    isWaiting = false;
}

void Subscriber::Register() 
{
    m_server.Acknoledge("", 0);
    std::thread t1([&] { WaitEvent(); });
    t1.detach();
}

void Subscriber::WaitEvent() {
    CryptoFactory fact;
    while (isWaiting) 
    {
        std::shared_ptr<uint8_t[]> message = m_server.WaitingRequest();
        std::shared_ptr<ICrypto> crypto = fact.Create(m_type);
        crypto->Deserialize(message);
        crypto->print();
    }
}
