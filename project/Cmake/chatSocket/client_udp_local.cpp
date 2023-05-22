#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/un.h>

//socket file
#define CLIENT_SOCK_FILE "client.sock"
#define SERVER_SOCK_FILE "server.sock"
#define BUFFER_SIZE 255
#define PORT 5050
char buffer[BUFFER_SIZE];
 
int main(int argc, char const *argv[]) {
    
    struct sockaddr_un server_address, client_address;      
    int socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);        

    if(socket_fd < 0){                          
        perror("Failed to create a socket");
        return 0;
    }

    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));
    client_address.sun_family = AF_UNIX;
    #define SERVER_SOCK_FILE "server.sock"
    strcpy(client_address.sun_path, CLIENT_SOCK_FILE);
    unlink(CLIENT_SOCK_FILE);
    bind(socket_fd, (struct sockaddr *)&client_address, sizeof(client_address));

    // Name the socket
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, SERVER_SOCK_FILE);

    socklen_t server_address_size = sizeof(server_address);
    while(1){
        std::string input;
        getline(std::cin, input);
     
        sendto(socket_fd, input.c_str(), input.length(),
            0, (const sockaddr *) &server_address, 
            sizeof(server_address));
        recvfrom(socket_fd, buffer, sizeof(buffer), 
                0, (struct sockaddr *) &server_address,
                &server_address_size);
        std::cout<<"response from server: " << buffer<<std::endl;
    }
    close(socket_fd);
    return 0;
}