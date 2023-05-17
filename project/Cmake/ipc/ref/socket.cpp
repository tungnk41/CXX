#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


//server
int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    int port = 12345;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }

    // Bind the socket to a specific address and port
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Accept a client connection
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        std::cerr << "Error accepting connection" << std::endl;
        return 1;
    }

    // Write to the socket
    std::string message = "Hello from the server!";
    strncpy(buffer, message.c_str(), sizeof(buffer));
    write(newsockfd, buffer, sizeof(buffer));

    // Close the socket
    close(newsockfd);
    close(sockfd);

    return 0;
}


//client

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

int main() {
    int sockfd, port;
    char buffer[1024];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    const char *hostname = "localhost";
    port = 12345;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }

    // Get the server by host name
    server = gethostbyname(hostname);
    if (server == nullptr) {
        std::cerr << "Error getting host" << std::endl;
        return 1;
    }

    // Set up the server address structure
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    // Read from the socket
    bzero(buffer, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));

    std::cout << "Message received: " << buffer << std::endl;

    // Close the socket
    close(sockfd);

    return 0;
}