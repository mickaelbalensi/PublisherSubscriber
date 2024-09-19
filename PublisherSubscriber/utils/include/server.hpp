#ifndef UDPSERVER_HPP
#define UDPSERVER_HPP

#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <memory>  // std::shared_ptr

#define BUFLEN 1024

class UDPServer {
public:
    UDPServer();
    std::shared_ptr<uint8_t[]> WaitingRequest();
    void Acknowledge(char *response, size_t size);
    ~UDPServer();

private:
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sockfd;
};

#endif // UDPSERVER_HPP
