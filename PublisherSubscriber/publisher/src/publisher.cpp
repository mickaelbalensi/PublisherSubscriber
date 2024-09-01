#include "publisher.hpp"

Publisher::Publisher(): m_isBroadcasting(true)
{
    thread t1(&Publisher::StartBroadcast, this);
    t1.detach();

    thread t2(&Publisher::Subscribe, this);
    t2.detach();
}

void Publisher::StartBroadcast()
{
    cout << "Start of broadcast" << endl;

    const char *message = "Hello World";
    m_udpClientBroadcast.SendBroadcast(PERIOD_BROADCAST, message, strlen(message));

    cout << "End of broadcast" << endl;
}

void Publisher::Subscribe()
{
    while (m_isBroadcasting)
    {
        sockaddr_in add;
        
        m_udpClientBroadcast.GetResponse(add);

        m_subscribers.push_back(add);
    }
}

void Publisher::EndBroadcast()
{
    m_isBroadcasting = false;
}

void Publisher::Publish(std::shared_ptr<ICrypto> cryptoPtr)
{
    for (sockaddr_in subscribAdd : m_subscribers)
    {
        cryptoPtr->print();
        std::shared_ptr<uint8_t[]> buffer = cryptoPtr->Serialize();
        m_udpClientBroadcast.SendTo((char *)buffer.get(), subscribAdd, cryptoPtr->GetSerializedSize());
    }
}

