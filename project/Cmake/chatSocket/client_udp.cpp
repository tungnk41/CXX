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
 
int main(int argc, char const *argv[]) {

    sockaddr_in server_address;
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);          
    if(socket_fd < 0){                                    //returns non negative integer if successful
        perror("Failed to create a socket");
        return 0;
    }
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    socklen_t server_address_size = sizeof(server_address);

    while(1){
        std::string input;
        getline(std::cin, input);
        sendto(socket_fd, input.c_str(), input.length(),
            0, (const sockaddr *) &server_address, 
            sizeof(server_address));
        memset(buffer,0,sizeof(buffer));
        recvfrom(socket_fd, buffer, sizeof(buffer), 
                0, (struct sockaddr *) &server_address,&server_address_size);
        std::cout<<"response from server: " << buffer<<std::endl;
    }
 
    close(socket_fd);
    
    return 0;
}