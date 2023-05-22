#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 256
#define SERVER_PORT 5050
#define IP "127.0.0.1"

void sendMessage(int socket_fd);
void receiveMessage(int socket_fd);
void print(std::string msg);
bool isStartsWith(const std::string& str, const std::string& prefix);

std::string username = "user";

int main(int argc,const char **argv,const char **envp){
    sockaddr_in client_address;

    username = std::string(argv[1])+":";
    //create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd == -1){
        print("Init socket failed!");
    }
    
    //Setup address and port
    memset(&client_address, 0, sizeof(client_address));
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(IP);
    client_address.sin_port = htons(SERVER_PORT);
    
    //connect to server
    if (connect(socket_fd, (sockaddr*)&client_address, sizeof(client_address)) == -1){
        print("Connect failed!");
    }
    std::string client_name = "[#]" + std::string(argv[1]);
    send(socket_fd, client_name.c_str(), client_name.length(), 0);
    
    std::thread sender(sendMessage, socket_fd);
    std::thread receiver(receiveMessage, socket_fd);
    
    sender.join();
    receiver.join();
    
    close(socket_fd);
    return 0;
}

void sendMessage(int socket_fd){
    std::string message;
    while(1){
        getline(std::cin, message);
        if (message == "quit"){
            close(socket_fd);
            exit(0);
        }
        std::string data = username + " " + message;
        send(socket_fd, data.c_str(), data.length(), 0);
    }
}

void receiveMessage(int socket_fd){
    char buffer[BUFFER_SIZE];
    while (1){
      
        int ret = recv(socket_fd, buffer, sizeof(buffer), 0); //length of message
        if (ret == -1){
            print("Connection is unsuccessful");
            exit(1);
        }
        if (ret == 0) {
            print("Connection is closed");
            exit(1);
        }
        if(isStartsWith(buffer,"[!]")) {
            print("username already exists. Please quit and enter with another name!!");
            exit(0);
        }
        else{
            print(buffer);
        }
        memset(buffer,0,sizeof(buffer));
    }
}


void print(std::string msg) {
    std::cout<<msg<<std::endl;
}

bool isStartsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    return str.substr(0, prefix.length()) == prefix;
}