#ifndef _UPIPE_H_
#define _UPIPE_H_
    #include <iostream>
    #include<unistd.h>
    #include<string>
    #define READ_FD 0
    #define WRITE_FD 1

    using std::cout;
    using std::endl;

    class UPipe {
    private:
        int fd[2];
    public:
        int createPipe();
        void uwrite(std::string msg);
        bool isParentProcess(pid_t pid);
        std::string uread();
        void test();
    };
#endif