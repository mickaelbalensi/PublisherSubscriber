#include "../include/server.hpp"
int PORT = 8888;

UDPServer::UDPServer() {
    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Socket creation failed");
        throw 1;
    }

    // Allow multiple subscribers to bind to the same port
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        close(sockfd);
        throw 1;
    }

    // Zero out the structure
    memset((char *)&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the port
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(sockfd);
        throw 1;
    }

    std::cout << "Server listening on port " << PORT << "...\n";
}

std::shared_ptr<uint8_t[]> UDPServer::WaitingRequest() {
    std::shared_ptr<uint8_t[]> buffer(new uint8_t[BUFLEN]);
    socklen_t client_len = sizeof(client_addr);

    int recv_len = recvfrom(sockfd, buffer.get(), BUFLEN, 0, 
                            (sockaddr *)&client_addr, &client_len);

    if (recv_len == -1) {
        perror("Receive failed");
        throw 2;
    }
    buffer[recv_len] = '\0';
    std::cout << "Received packet from " << inet_ntoa(client_addr.sin_addr) 
              << ":" << ntohs(client_addr.sin_port) << "\n";
    std::cout << "Data: " << buffer << "\n";

    return buffer;
}

void UDPServer::Acknoledge(char *response, size_t size) {
    close(sockfd);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) 
    {
        perror("Socket creation failed");
        throw 1;
    }

    server_addr.sin_port = htons(0); // Let the OS choose an available port

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) 
    {
        perror("Bind failed");
        close(sockfd);
        throw 1;
    }

    // Get the assigned port number
    socklen_t len = sizeof(server_addr);
    if (getsockname(sockfd, (struct sockaddr *)&server_addr, &len) == -1) {
        perror("getsockname failed");
    } else {
        printf("Bound to port: %d\n", ntohs(server_addr.sin_port));
    }


    socklen_t client_len = sizeof(client_addr);

    if (sendto(sockfd, response, size, 0, 
               (sockaddr *)&client_addr, client_len) == -1) {
        perror("Send failed");
    } else {
        std::cout << "Response sent to " << inet_ntoa(client_addr.sin_addr) << "\n";
    }
}

UDPServer::~UDPServer() {
    close(sockfd);
}
