#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <chrono>            // std::chrono::seconds
#include <thread>            // std::this_thread::sleep_for
#include <memory>                // std::shared_ptr

#define PORT 8888
#define BROADCAST_IP "255.255.255.255"
#define BUFLEN 1024

#ifndef CLIENT_HPP
#define CLIENT_HPP

class UDPClientBroadcast {
public:
    UDPClientBroadcast();
    ~UDPClientBroadcast();
    
    void SendBroadcast(const std::chrono::seconds period, const char *message, 
                                                                size_t size);

    void SendTo(const char *message, const sockaddr_in& destination, size_t size);

    std::shared_ptr<char[]> GetResponse(sockaddr_in& addr_in);

private:
    struct sockaddr_in broadcast_addr;
    struct sockaddr_in server_addr;
    int sockfd;      
};

#endif