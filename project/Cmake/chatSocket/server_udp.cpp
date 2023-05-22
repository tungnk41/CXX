#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/un.h>

#define BUFFER_SIZE 255
#define PORT 5050
char buffer[BUFFER_SIZE];


int main(int argc, char const *argv[])
{
    struct sockaddr_in server_address, client_address;                                                                  
    // Get a socket file descriptor
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);           

    if(socket_fd < 0){                                         
        perror("Failed to create a socket");
        return 0;
    }

    memset(&server_address, 0, sizeof(server_address));                 
    memset(&client_address, 0, sizeof(client_address));
    server_address.sin_family    = AF_INET;                       // IPv4
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    // Bind the socket to the protocol address (IP + port number) 
    if(bind(socket_fd, (sockaddr*) &server_address, sizeof(server_address)) < 0){
        perror("Bind failed");
        return 0;
    }

    socklen_t client_address_size = sizeof(client_address);
    while(1){
        recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address,&client_address_size);                                           
        sendto(socket_fd, buffer, sizeof(buffer),
        0, (const sockaddr *) &client_address,client_address_size);
    }
    close(socket_fd);
    return 0;
}