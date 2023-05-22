#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

#include <sys/un.h>
#define MAX 255
#define PORT 5050

# define CLIENT_SOCK_FILE "client.sock"
# define SERVER_SOCK_FILE "server.sock"


using namespace std;
 
int main(int argc, char const *argv[]) {

    char buffer[MAX];
    char str[MAX];
    int port_no = PORT;
    
    struct sockaddr_in servaddr;
    struct sockaddr_un server_address, client_address;
 
    // int sockfd = socket(AF_INET, SOCK_DGRAM, 0);        
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);        

    if(sockfd < 0){                                    //returns non negative integer if successful
        perror("Failed to create a socket");
        return 0;
    }

    //We do not bind the socket to a port for a client because it does not matter
    //which port you use to send the data
    //The port that receives the data is important so we bind the socket in
    // the server program

    // memset(&servaddr, 0, sizeof(servaddr));
    // // Filling server information
    // servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = INADDR_ANY;
    // servaddr.sin_port = htons(port_no);

        // Name the socket then bind
    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));
    client_address.sun_family = AF_UNIX;
    strcpy(client_address.sun_path, CLIENT_SOCK_FILE);
    unlink(CLIENT_SOCK_FILE);
    bind(sockfd, (struct sockaddr *)&client_address, sizeof(client_address));

    // Name the socket
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, SERVER_SOCK_FILE);

     
    int n;
    socklen_t len = sizeof(server_address);

    while(1){

        fgets(str, MAX, stdin);
     
        sendto(sockfd, (const char *)str, strlen(str),
            0, (const struct sockaddr *) &server_address, 
            sizeof(server_address));
    
         
        n = recvfrom(sockfd, (char *)buffer, MAX, 
                0, (struct sockaddr *) &server_address,
                &len);

        buffer[n] ='\0';
        std::cout<<"server data: " << buffer<<std::endl;
    }
 
    close(sockfd);
    
    return 0;
}