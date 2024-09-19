#include "subscriber.hpp"
const size_t BUFFLEN = 1024;

Subscriber::Subscriber(CLIENT_TYPE type)
    : m_type(type), isWaiting(true), m_id(0)
{
    m_server.WaitingRequest();
    Register();
}

Subscriber::~Subscriber()
{
    isWaiting = false;
}

void Subscriber::Register()
{
    m_server.Acknowledge("", 0);

    const_cast<uid_t&>(m_id) = *(uid_t*)m_server.WaitingRequest().get();
    std::cout << "ID: " << m_id << std::endl;

    std::thread t1([&] { WaitEvent(); });
    t1.detach();
}

void Subscriber::WaitEvent()
{
    CryptoFactory fact;
    while (isWaiting)
    {
        std::cout << "Waiting event of type " << (m_type == CLIENT_TYPE::CLASSIC ? 
                    "CLASSIC" : 
                    "PREMIUM") 
                    << "" << std::endl;
        std::shared_ptr<uint8_t[]> message = m_server.WaitingRequest();
        std::shared_ptr<ICrypto> crypto = fact.Create(m_type);
        try
        {
            crypto->Deserialize(message);
            crypto->print();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}