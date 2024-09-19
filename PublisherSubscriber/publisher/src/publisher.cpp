#include "publisher.hpp"

Publisher::Publisher(): 
    m_isBroadcasting(true), 
    m_totalSubscribers(0)
{
    thread t1(&Publisher::StartBroadcast, this);
    t1.detach();

    thread t2(&Publisher::Subscribe, this);
    t2.detach();
}

void Publisher::StartBroadcast()
{
    cout << "Start of broadcast" << endl;

    while (m_isBroadcasting)
    {
        std::this_thread::sleep_for(PERIOD_BROADCAST);
        const char *message = "Hello World";
        m_udpClientBroadcast.SendBroadcast(PERIOD_BROADCAST, message, strlen(message));
    }

    cout << "End of broadcast" << endl;
}

void Publisher::Subscribe()
{
    while (m_isBroadcasting)
    {
        sockaddr_in add;

        
        m_udpClientBroadcast.GetResponse(add);

        m_subscribers[++m_totalSubscribers] = add;
        m_udpClientBroadcast.SendTo((char *)&m_totalSubscribers, add, \
                                                    sizeof(m_totalSubscribers));
    }
}

void Publisher::EndBroadcast()
{
    m_isBroadcasting = false;
}

void Publisher::Publish(std::shared_ptr<ICrypto> cryptoPtr)
{
    std::shared_ptr<uint8_t[]> buffer = cryptoPtr->Serialize();

    m_udpClientBroadcast.SendBroadcast(PERIOD_BROADCAST, (char *)buffer.get(),\
                                                cryptoPtr->GetSerializedSize());
    
    /* for (const auto& [_, subscribAdd] : m_subscribers)
    {
        //cryptoPtr->print();
        std::shared_ptr<uint8_t[]> buffer = cryptoPtr->Serialize();
        m_udpClientBroadcast.SendTo((char *)buffer.get(), subscribAdd, cryptoPtr->GetSerializedSize());
    } */ 
}

