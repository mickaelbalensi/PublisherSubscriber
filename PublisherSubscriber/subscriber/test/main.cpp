#include "../include/subscriber.hpp"
#include <thread>
#include <chrono>

int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        std::cout << "Usage: ./main [1] " << std::endl;
        return 0;
    }
    
    CLIENT_TYPE type = strncmp(argv[1], "1", 1) == 0 ? CLIENT_TYPE::CLASSIC: CLIENT_TYPE::PREMIUM;

    Subscriber subscriber(type);
    std::this_thread::sleep_for(std::chrono::seconds(30));
    return 0;
}
