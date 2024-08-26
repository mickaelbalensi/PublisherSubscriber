#include "../include/publisher.hpp"
#include "../../utils/include/shapeFactory.hpp"

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

    //while (m_isBroadcasting)
    {
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
        
        std::shared_ptr<char[]> buffer = m_udpClientBroadcast.GetResponse(add);

        /* SHAPE shape = *(SHAPE*)(buffer.get()); */

        size_t len = *(size_t *)(buffer.get());
        size_t offset = sizeof(size_t);

        for (size_t i = 0; i < len; i++)
        {
            SHAPE shape = *(SHAPE*)(buffer.get() + offset);
            offset += sizeof(SHAPE);
            m_subscribers[shape].push_back(add);
        }

        //m_subscribers[shape].push_back(add); /* here */
    }
}

void Publisher::EndBroadcast()
{
    m_isBroadcasting = false;
}

void Publisher::Publish(SHAPE shape, std::shared_ptr<IShape> shapePtr)
{
    if (m_subscribers.find(shape) != m_subscribers.end())
    {
        shapePtr->print();
        for (sockaddr_in subscribAdd : m_subscribers[shape])
        {
            std::shared_ptr<uint8_t[]> buffer = shapePtr->Serialize();
            m_udpClientBroadcast.SendTo((char *)buffer.get(), subscribAdd, shapePtr->GetSerializedSize());
        }
    }
}

