#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key;
    int shmid;
    char *sharedMemory;

    // Generate a unique key
    key = ftok("shared_memory_example", 65);

    // Create or get the shared memory segment
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach the shared memory segment
    sharedMemory = (char *)shmat(shmid, (void *)0, 0);

    // Write to the shared memory
    std::string message = "Hello from the writer process!";
    strncpy(sharedMemory, message.c_str(), 1024);

    // Read from the shared memory
    std::cout << "Message received: " << sharedMemory << std::endl;

    // Detach the shared memory segment
    shmdt(sharedMemory);

    // Mark the shared memory segment for deletion
    shmctl(shmid, IPC_RMID, nullptr);

    return 0;
}