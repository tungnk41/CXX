#include <mq.h>

void MessageQueue::runReceiver(int anotherID) {
    cout<<"runReceiver"<<endl;
    std::string buff;
    mq_msg msg;
    msg.type = anotherID;
    while(1) {
         int ret = msgrcv(msgID, &msg, sizeof(msg), msg.type, 0);
         if(ret != -1) {
            cout <<"Received: " <<msg.data<<endl;
         }
    }
};

void MessageQueue::runSender(int anotherID) {
    std::string buff;
    mq_msg msg;
    msg.type = anotherID;
    while(1) {
        cin >> buff;
        std::strcpy(msg.data, buff.c_str());
        cout << "Send: " << msg.data <<endl;
        msgsnd(msgID, &msg, sizeof(msg), 0);

    }
};

void MessageQueue::run() {
    cout <<"Started"<<endl;
    int id = -1;
    int anotherID = -1;
    cout <<"create ID: " <<endl;
    cin >> id;
    cout <<"communicate with ID: " <<endl;
    cin >> anotherID;
    std::thread reader([this](int id){
        runReceiver(id);
    }, id);
    reader.detach();
    runSender(anotherID);

};