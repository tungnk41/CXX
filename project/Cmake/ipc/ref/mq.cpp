#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Structure for the message
struct Message {
    long mtype;     // Message type
    char mtext[50]; // Message data
};

int main() {
    key_t key;
    int msgid;
    Message message;

    // Generate a unique key
    key = ftok("message_queue_example", 65);

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Prepare the message
    message.mtype = 1; // Message type can be any positive number
    strncpy(message.mtext, "Hello from the sender process!", sizeof(message.mtext));

    // Send the message
    msgsnd(msgid, &message, sizeof(message.mtext), 0);

    std::cout << "Message sent: " << message.mtext << std::endl;

    return 0;
}

int main() {
    key_t key;
    int msgid;
    Message message;

    // Generate the same unique key as the sender process
    key = ftok("message_queue_example", 65);

    // Get the message queue ID
    msgid = msgget(key, 0666);

    // Receive the message
    msgrcv(msgid, &message, sizeof(message.mtext), 1, 0);

    std::cout << "Message received: " << message.mtext << std::endl;

    // Remove the message queue
    msgctl(msgid, IPC_RMID, nullptr);

    return 0;
}