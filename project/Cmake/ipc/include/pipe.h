#ifndef _PIPE_H_
#define _PIPE_H_
    #include <iostream>
    #include <unistd.h>
    #include <fcntl.h>
    #include <string>
    #include <sys/types.h>
    #include <sys/stat.h>


    using std::cout;
    using std::endl;
    using std::cin;

    class Pipe {
        private:
            std::string pipefifo = "/tmp/pipefifo";  
            void createFifo();
            void createReader();
            void createSender();
        public:
            Pipe() {
                createFifo();
            };
            void create(int type);
            void test();
     
    };
#endif