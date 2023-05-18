#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unordered_map>
 #include <stdarg.h>

#define SERVER_PORT 5208 
#define BUF_SIZE 1024
#define MAX_CLNT 256    

void handle_clnt(int clnt_sock);
void send_msg(const std::string &msg);
int output(const char *arg,...);
int error_output(const char *arg,...);
void error_handling(const std::string &message);

int clnt_cnt = 0;
std::mutex mtx;
std::unordered_map<std::string, int>clnt_socks;

int main(int argc,const char **argv,const char **envp){
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serv_sock == -1){
        error_handling("socket() failed!");
    }
    memset(&serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // serv_addr.sin_port=htons(atoi(argv[1]));
    serv_addr.sin_port = htons(SERVER_PORT);

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() failed!");
    }
    printf("the server is running on port %d\n", SERVER_PORT);
    if (listen(serv_sock, MAX_CLNT) == -1){
        error_handling("listen() error!");
    }

    while(1){  
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1){
            error_handling("accept() failed!");
        }
        mtx.lock();
        clnt_cnt++;
        mtx.unlock();

        std::thread th(handle_clnt, clnt_sock);
        th.detach();

        output("Connected client IP: %s \n", inet_ntoa(clnt_addr.sin_addr));
    }
    close(serv_sock);
    return 0;
}

void handle_clnt(int clnt_sock){
    char msg[BUF_SIZE];
    int flag = 0;

    char tell_name[8] = "client:";
    while(recv(clnt_sock, msg, sizeof(msg),0) != 0){
        std::cout<<"#### " << msg <<std::endl;
        if (std::strlen(msg) > std::strlen(tell_name)) {
            char pre_name[8];
            std::strncpy(pre_name, msg, 7);
            pre_name[7] = '\0';
            if (std::strcmp(pre_name, tell_name) == 0) {
                char name[20];
                std::strcpy(name, msg+7);
                if(clnt_socks.find(name) == clnt_socks.end()){
                    output("the name of socket %d: %s\n", clnt_sock, name);
                    clnt_socks[name] = clnt_sock;
                }
                else {
                    std::string error_msg = std::string(name) + " exists already. Please quit and enter with another name!";
                    send(clnt_sock, error_msg.c_str(), error_msg.length()+1, 0);
                    mtx.lock();
                    clnt_cnt--;
                    mtx.unlock();
                    flag = 1;
                }
            }
        }

        if(flag == 0)
            send_msg(std::string(msg));
    }
    if(flag == 0){
        // 客户端关闭连接，从clnt_socks中删除此客户端
        std::string leave_msg;
        std::string name;
        mtx.lock();
        auto it = clnt_socks.begin();
        while(it != clnt_socks.end()) {
            if(it->second == clnt_sock){
                name = it->first;
                clnt_socks.erase(it->first);
                break;
            }
            it++;
        }
        // for (auto it = clnt_socks.begin(); it != clnt_socks.end(); ++it ){
        //     if(it->second == clnt_sock){
        //         name = it->first;
        //         clnt_socks.erase(it->first);
        //     }
        // }
        clnt_cnt--;
        mtx.unlock();
        leave_msg = "client " + name + " leaves the chat room";
        send_msg(leave_msg);
        output("client %s leaves the chat room\n", name.c_str());
        close(clnt_sock);
    }
    else {
        close(clnt_sock);
    }
}

void send_msg(const std::string &msg){
    mtx.lock();
    // 私聊msg格式: [send_clnt] @recv_clnt message
    // 判断[send_clnt] 后是否为@ 若是则是私聊
    std::string pre = "@";
    int first_space = msg.find_first_of(" ");
    if (msg.compare(first_space+1, 1, pre) == 0){
        // 单播
        // space为recv_clnt和消息间的空格
        int space = msg.find_first_of(" ", first_space+1);
        std::string receive_name = msg.substr(first_space+2, space-first_space-2);
        std::string send_name = msg.substr(1, first_space-2);
        if(clnt_socks.find(receive_name) == clnt_socks.end()) {
            // 如果私聊的用户不存在
            std::string error_msg = "[error] there is no client named " + receive_name;
            send(clnt_socks[send_name], error_msg.c_str(), error_msg.length()+1, 0);
        }
        else {
            send(clnt_socks[receive_name], msg.c_str(), msg.length()+1, 0);
            send(clnt_socks[send_name], msg.c_str(), msg.length()+1, 0);
        }
    }
    else {
        // 广播
        for (auto it = clnt_socks.begin(); it != clnt_socks.end(); it++) {
            send(it->second, msg.c_str(), msg.length()+1, 0);
        }
    }
    mtx.unlock();
}

int output(const char *arg, ...){
    int res;
    va_list ap;
    va_start(ap, arg);
    res = vfprintf(stdout, arg, ap);
    va_end(ap);
    return res;
}

int error_output(const char *arg, ...){
    int res;
    va_list ap;
    va_start(ap, arg);
    res = vfprintf(stderr, arg, ap);
    va_end(ap);
    return res;
}

void error_handling(const std::string &message){
    std::cerr<<message<<std::endl;
    exit(1);
}