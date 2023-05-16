#include <mq.h>

void MessageQueue::createReader() {
    std::string buff;
    mq_msg msg;
    msg.type = 1;
    while(1) {
         int ret = msgrcv(msgID, &msg, sizeof(msg), msg.type, 0);
         if(ret != -1) {
            cout <<"Receive: " <<msg.data<<endl;
         }
    }
};

void MessageQueue::createSender() {
    std::string buff;
    mq_msg msg;
    msg.type = 1;
    while(1) {
        cin >> buff;
        std::strcpy(msg.data, buff.c_str());
        cout << "Send: " << msg.data <<endl;
        msgsnd(msgID, &msg, sizeof(msg), 0);

    }
};

void MessageQueue::create(int type) {
    if(type == 1) {
        createReader();
    }
    else {
        createSender();
    }
};

void MessageQueue::test() {
    MessageQueue mq;
    int type;

    cout << "1: Reader "<<endl<<"2: Sender"<<endl;
    cin >> type;
    mq.create(type);
};