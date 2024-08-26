#include "./utils/include/shapes.hpp"
#include "./utils/include/server.hpp"

int main()
{

    UDPServer server;
    auto buffer = server.WaitingRequest();
    Circle circle(8);
    circle.print();

    circle.Deserialize(buffer);
    circle.print();


    return 0;
}









