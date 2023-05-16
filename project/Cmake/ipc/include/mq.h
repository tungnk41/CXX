#ifndef _MQ_H_
#define _MQ_H_
    #include <iostream>
    #include <string>
    #include <cstring>
    #include <sys/ipc.h>
    #include <sys/msg.h>

    #define BUFFER_SIZE 256
    using std::cout;
    using std::endl;
    using std::cin;

    struct mq_msg {
        long type;
        char data[BUFFER_SIZE];
    };

    class MessageQueue {
        private:
            key_t key;
            int msgID;
            void createReader();
            void createSender();
        public:
            MessageQueue() {
                key = ftok("msqueue", 1001); //pathname , projectID
                msgID =  msgget(key, 0666 | IPC_CREAT);
            }
            ~MessageQueue() {
                 // to destroy the message queue
                msgctl(msgID, IPC_RMID, NULL);
            }
            void create(int type);
            void test();
     
    };
#endif