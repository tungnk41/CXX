
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
#define SERVER_SOCK_FILE "build/server.sock"
char buffer[BUFFER_SIZE];

int main(int argc, char const *argv[])
{
    struct sockaddr_un server_address, client_address;          
    int socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);           

    if(socket_fd < 0){                                    
        perror("Failed to create a socket");
        return 0;
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, SERVER_SOCK_FILE);
    unlink(SERVER_SOCK_FILE);

    if(bind(socket_fd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0){
        perror("Bind failed");
        return 0;
    }

    socklen_t client_address_size = sizeof(client_address);
    while(1){
        memset(buffer,0,sizeof(buffer));
        recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address, &client_address_size);                                                
        sendto(socket_fd, buffer, sizeof(buffer), 
        0, (const sockaddr *) &client_address,client_address_size);
    }
    close(socket_fd);
    return 0;
}