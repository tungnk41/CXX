#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024
#define SERVER_PORT 5050
#define IP "127.0.0.1"

void sendMessage(int socket);
void receiveMessage(int socket);
void print(std::string msg);
bool startsWith(const std::string& str, const std::string& prefix);

std::string username = "user";
int socketClient = -1;
std::string message;

int main(int argc,const char **argv,const char **envp){
    struct sockaddr_in socketAddress;

    username = std::string(argv[1])+":";
    //create socket
    int socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketClient == -1){
        print("Init socket failed!");
    }
    
    //Setup address and port
    memset(&socketAddress, 0, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = inet_addr(IP);
    socketAddress.sin_port = htons(SERVER_PORT);
    
    //connect to server
    if (connect(socketClient, (struct sockaddr*)&socketAddress, sizeof(socketAddress)) == -1){
        print("Connect failed!");
    }
    std::string clientName = "[#]" + std::string(argv[1]);
    send(socketClient, clientName.c_str(), clientName.length() + 1, 0);
    
    std::thread sender(sendMessage, socketClient);
    std::thread receiver(receiveMessage, socketClient);
    
    sender.join();
    receiver.join();
    
    close(socketClient);
    return 0;
}

void sendMessage(int socket){
    while(1){
        getline(std::cin, message);
        if (message == "quit"){
            close(socket);
            exit(0);
        }
        std::string data = username + " " + message;
        send(socket, data.c_str(), data.length() + 1, 0);
    }
}

void receiveMessage(int socket){
    char data[BUF_SIZE + username.length() + 1];
    while (1){
        int ret = recv(socket, data, BUF_SIZE+username.length() + 1, 0); //length of message
        if (ret == -1){
            print("Connection is unsuccessful");
            exit(1);
        }
        if (ret == 0) {
            print("Connection is closed");
            exit(1);
        }
        if(startsWith(data,"[!]")) {
            print("username already exists. Please quit and enter with another name!!");
            exit(0);
        }
        else{
            print(data);
        }
    }
}


void print(std::string msg) {
    std::cout<<msg<<std::endl;
}

bool startsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    return str.substr(0, prefix.length()) == prefix;
}