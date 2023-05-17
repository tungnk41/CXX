#include <iostream>
#include <cstring>
#include <csignal>
#include <unistd.h>

// Signal handler function
void signalHandler(int signalNumber) {
    std::cout << "Received signal: " << signalNumber << std::endl;
}

int main() {
    // Register the signal handler
    signal(SIGUSR1, signalHandler);

    // Get the process ID
    pid_t pid = getpid();

    // Send a signal to the process
    kill(pid, SIGUSR1);

    return 0;
}