#ifndef _PIPE_HPP_
#define _PIPE_HPP_
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
            void runReceiver();
            void runSender();
        public:
            Pipe() {
                createFifo();
            };
            void create(int type);
            void run();
     
    };
#endif