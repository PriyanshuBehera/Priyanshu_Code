#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>

#define MAX_PACKET_SIZE 65536

int main() {
    int raw_socket;
    struct ip* ip_header;
    struct icmphdr* icmp_header;
    char buffer[MAX_PACKET_SIZE];
    ssize_t packet_size;

    // Create a raw socket to capture ICMP packets
    raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (raw_socket < 0) {
        perror("Socket creation error");
        exit(1);
    }

    while (1) {
        packet_size = recvfrom(raw_socket, buffer, sizeof(buffer), 0, NULL, NULL);
        if (packet_size < 0) {
            perror("Packet receive error");
            exit(1);
        }

        ip_header = (struct ip*)buffer;
        icmp_header = (struct icmphdr*)(buffer + (ip_header->ip_hl << 2)); // Move to the ICMP header

        // Print the length of the IP header of the captured ICMP packet
        printf("Length of IP Header: %d bytes\n", ip_header->ip_hl << 2);
    }

    close(raw_socket);
    return 0;
}
