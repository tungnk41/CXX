#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>

#include <sys/un.h>

#define MAX 255
#define PORT 5050
#define SERVER_SOCK_FILE "server.sock"


using namespace std;


int main(int argc, char const *argv[])
{

    struct sockaddr_in servaddr, cliaddr;
    struct sockaddr_un server_address, client_address;
    int port_no = PORT;
    char buffer[MAX];                                       //holds the string received from client
    char str[MAX];                                          //holds the string to be sent to the client

    // Get a socket file descriptor
    // int sockfd = socket(AF_INET, SOCK_DGRAM, 0);           
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);           

    if(sockfd < 0){                                         //returns non negative integer if successful
        perror("Failed to create a socket");
        return 0;
    }

    memset(&server_address, 0, sizeof(server_address));                 // initialize both to 0
    memset(&client_address, 0, sizeof(client_address));

    // servaddr.sin_family    = AF_INET;                       // IPv4
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(port_no);




    // Bind the socket to the protocol address (IP + port number) 
    // if(bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0){
    //     perror("Bind failed");
    //     return 0;
    // }

     memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, SERVER_SOCK_FILE);
    unlink(SERVER_SOCK_FILE);

    if(bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0){
        perror("Bind failed");
        return 0;
    }

    int n;
    socklen_t len = sizeof(client_address);

    while(1){
        
        n = recvfrom(sockfd, (char *)buffer, MAX, 
                0, (struct sockaddr *) &client_address,          //cliaddr stores the address of the client which sent data to the server
            &len);                                                 // which is used in the sendto() function to identify which client data must be sent to

        buffer[n] = '\0';
        std::cout<<buffer<<std::endl;

        // fgets(str, MAX, stdin);
        ssize_t m = sendto(sockfd, (const char *)buffer, strlen(buffer), 
        0, (const struct sockaddr *) &client_address,
            len);
    }

    close(sockfd);
    
    return 0;
}