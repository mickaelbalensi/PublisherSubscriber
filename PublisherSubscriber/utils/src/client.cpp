#include "../include/client.hpp"

UDPClientBroadcast::UDPClientBroadcast()
{
    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Socket creation failed");
        throw 1;
    }

    int broadcastEnable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) == -1) {
        perror("Setting broadcast option failed");
        close(sockfd);
        throw 1;
    }

    // Zero out the structure
    memset((char *)&broadcast_addr, 0, sizeof(broadcast_addr));

    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);
}

UDPClientBroadcast::~UDPClientBroadcast()
{
    close(sockfd);
}

void UDPClientBroadcast::SendBroadcast(const std::chrono::seconds period, const char *message, size_t size)
{
    //while (true)
    {
        std::this_thread::sleep_for(period);

        // Send the broadcast message
        if (sendto(sockfd, message, size, 0, 
            (sockaddr *)&broadcast_addr, sizeof(broadcast_addr)) == -1) 
        {
            perror("Send failed");
            close(sockfd);
            throw 1;
        }
        std::cout << "Broadcast message sent: " << message << "\n";
    }
}

void UDPClientBroadcast::SendTo(const char *message, const sockaddr_in &destination, size_t size)
{
    if (sendto(sockfd, message, size, 0, (sockaddr *)&destination, 
                                                    sizeof(destination)) == -1) 
    {
        perror("Send failed");
        close(sockfd);
        throw 1;
    }
    std::cout << "Message sent: " << message << "\n";
}

std::shared_ptr<char[]> UDPClientBroadcast::GetResponse(sockaddr_in& addr_in)
{
    socklen_t server_len = sizeof(addr_in);
    std::shared_ptr<char[]> buffer(new char[BUFLEN]);
    int recv_len = recvfrom(sockfd, buffer.get(), BUFLEN, 0, 
                            (sockaddr *)&addr_in, &server_len);
    if (recv_len == -1) {
        perror("Receive failed");
    } else {
        buffer[recv_len] = '\0';
        std::cout << "Received response from server: " << buffer << "\n";
    }

    return buffer;
}
