#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;

// Macro to check if the system is little-endian
#define IS_LITTLE_ENDIAN() (*(uint16_t *)"\0\x0f" > 0x100)

int is_little_endian() {
    short sh = 0x0201;

    char *p = (char *)&sh;
    if (*p == 1) {
        return 1;
    }
    else if (*p == 2) {
        return 0;
    }

    return  3;
}

void print_bytes(void *ptr, size_t size) {
    unsigned char *bytes = (unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02x ", bytes[i]);
    }
    printf("\n");
}

int main() {

    cout << "is_little_endian ? " << is_little_endian() << endl;


    char arr[3] = "\0\x0f";

    arr[1] = 'R';

    cout << "arr[0] " << arr[0] <<  endl;
    cout << "arr[1] " << arr[1] <<  endl;
    cout << "is little ? " << (*(uint16_t *)arr > 0x100) << endl; 

    uint32_t num = 0x12345678;

    cout << "(0xf > 0x100) ? " <<(0xf > 0x100) << endl;

    // Check the system's endianness
    if (IS_LITTLE_ENDIAN()) {
        printf("System is little-endian.\n");
    } else {
        printf("System is big-endian.\n");
    }

    // Print the original number
    printf("Original number (hex): 0x%x\n", num);
    printf("Bytes of the original number: ");
    print_bytes(&num, sizeof(num));

    // Convert from host to network byte order (big-endian)
    uint32_t network_order = ntohl(num);
    printf("Network order (hex): 0x%x\n", network_order);
    printf("Bytes of the network order: ");
    print_bytes(&network_order, sizeof(network_order));

    // Convert back from network to host byte order
    uint32_t host_order = htonl(network_order);
    printf("Host order (hex): 0x%x\n", host_order);
    printf("Bytes of the host order: ");
    print_bytes(&host_order, sizeof(host_order));

    return 0;
}