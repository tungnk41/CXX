#ifndef _MQ_HPP_
#define _MQ_HPP_
    #include <iostream>
    #include <string>
    #include <cstring>
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include <thread>

    #define BUFFER_SIZE 256
    using std::cout;
    using std::endl;
    using std::cin;

    struct Message {
        long receiveID;
        char data[BUFFER_SIZE];
    };

    class MessageQueue {
        private:
            key_t key;
            int msgID;
        public:
            MessageQueue() {
                key = ftok("msqueue", 1001); //pathname , projectID
                msgID =  msgget(key, 0666 | IPC_CREAT);
            }
            ~MessageQueue() {
                 // to destroy the message queue
                msgctl(msgID, IPC_RMID, NULL);
            }
            void runReceiver(int id);
            void runSender(int id);
            void run();
     
    };
#endif