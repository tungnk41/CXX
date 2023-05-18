#include <message_queue.hpp>

void MessageQueue::runReceiver(int id) {
    std::string buff;
    Message msg;
    msg.receiveID = id;
    while(1) {
         int ret = msgrcv(msgID, &msg, sizeof(msg), msg.receiveID, 0);
         if(ret != -1) {
            cout <<"Receive: "<<msg.data<<endl;
         }
    }
};

void MessageQueue::runSender(int id) {
    std::string buff;
    Message msg;
    msg.receiveID = id;
    while(1) {
        cin >> buff;
        std::strcpy(msg.data, buff.c_str());
        cout << "Send: "<<  msg.data <<endl;
        msgsnd(msgID, &msg, sizeof(msg), 0);

    }
};

void MessageQueue::run() {
    cout <<"Started"<<endl;
    int id = -1;
    int receiveID = -1;
    cout <<"ID: ";
    cin >> id;
    cout <<"Send to ID: ";
    cin >> receiveID;
    std::thread reader([this](int id){
        runReceiver(id);
    }, id);
    reader.detach();
    runSender(receiveID);

};