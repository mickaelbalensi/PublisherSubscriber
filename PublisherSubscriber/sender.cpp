#include "./utils/include/shapes.hpp"
#include "./utils/include/client.hpp"
#include <iostream>

using namespace std;

int main()
{
    UDPClientBroadcast client;
    Circle circle(3);
    /* circle.m_color = COLORS(9);
    circle.m_coordinates.m_latitude = 6;
    circle.m_coordinates.m_longitude = 7; */

    auto buffer = circle.Serialize();
    cout << "circle.GetSize() = " << circle.GetSerializedSize();

    auto circleDeserialized = std::make_shared<Circle>(1);
    circleDeserialized->Deserialize(buffer);
    circleDeserialized->print();



    client.SendBroadcast(1s, (char *)buffer.get(), circle.GetSerializedSize());




    return 0;
}


