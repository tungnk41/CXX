#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unordered_map>
#include <signal.hpp>


#define SERVER_PORT 5050 
#define BUFFER_SIZE 1024
#define MAX_CLIENT 256    

void handleSocketConnection(int socket_client_fd);
void sendMessage(const std::string &msg);
void print(std::string msg);
bool isStartsWith(const std::string& str, const std::string& prefix);
void removePattern(std::string& str, const std::string& pattern);
void handleSignalTerminate(int signal_id);

int socket_server_fd = -1;
int total_client = 0;
std::mutex mtx;
std::unordered_map<std::string, int> socket_client_fds;

int main(int argc,const char **argv,const char **envp){

    //Register signal to listen cancel process
    Signal sig;
    sig.registerSignal(SIGINT,handleSignalTerminate);


    //Socket address
    sockaddr_in server_address, client_address;


    //create socket
    socket_server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_server_fd == -1){
        print("create socket failed!");
        exit(1);
    }

    //setup address and port
    memset(&server_address,0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    // server_address.sin_port=htons(atoi(argv[1]));
    server_address.sin_port = htons(SERVER_PORT);


    //bind socket with address
    if (bind(socket_server_fd, (sockaddr*)&server_address, sizeof(server_address)) == -1){
        print("bind failed!");
        exit(1);
    }
    printf("the server is running on port %d\n", SERVER_PORT);

    //listen connection to socket
    if (listen(socket_server_fd, MAX_CLIENT) == -1){
        print("listen failed");
        exit(1);
    }

    socklen_t client_address_size;
    while(1){
        client_address_size = sizeof(client_address);  
        int socket_client_fd = accept(socket_server_fd, (sockaddr*)&client_address, &client_address_size);
        if (socket_client_fd == -1){
            print("accept failed!");
            exit(1);
        }
        std::thread handler(handleSocketConnection, socket_client_fd);
        handler.detach();
    }
    close(socket_server_fd);
    return 0;
}

void handleSocketConnection(int socket_client_fd){
    char buffer[BUFFER_SIZE];
    std::string username = "";
    int ret = 0;
    bool is_duplicated = false;
    while((ret = recv(socket_client_fd, buffer, sizeof(buffer),0)) != 0){
        print(std::string("Received: ").append(buffer));
        std::string received_data = std::string(buffer);
        if(isStartsWith(received_data,"[#]")) {
            removePattern(received_data,"[#]");
            username = received_data;
            if(socket_client_fds.count(username) > 0){
                std::string error_msg = "[!]";
                send(socket_client_fd, error_msg.c_str(), error_msg.length()+1, 0);
                is_duplicated = true;
            }
            else {
                socket_client_fds[username] = socket_client_fd;
                std::string msg = username + " joined!";
                mtx.lock();
                total_client++;
                mtx.unlock();
                sendMessage(msg);
            }
        }
        else {
            sendMessage(received_data);
        }
    }
    if(ret == 0 && !is_duplicated){
        std::string leave_msg;
        mtx.lock();
        if(socket_client_fds.count(username) > 0) {
            socket_client_fds.erase(username);
        }
        mtx.unlock();
        leave_msg = username + " has left the chat room";
        sendMessage(leave_msg);
        close(socket_client_fd);
    }
    else {
        close(socket_client_fd);
    }
}

void sendMessage(const std::string &msg){
    print(msg);
    for (auto const& it : socket_client_fds) {
        send(it.second, msg.c_str(), msg.length()+1, 0);
    }
}

void print(std::string msg) {
    std::cout <<"Server --->> " << msg << std::endl;
}

bool isStartsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    return str.substr(0, prefix.length()) == prefix;
}

void removePattern(std::string& str, const std::string& pattern) {
    size_t pos = 0;
    while ((pos = str.find(pattern, pos)) != std::string::npos) {
        str.erase(pos, pattern.length());
    }
}

void handleSignalTerminate(int signal_id) {
    print("Captured Signal: " + std::to_string(signal_id));
    close(::socket_server_fd);
    exit(0);
}