#include <iostream>
#include <unistd.h>

int main() {
    int pipefd[2];
    int bufferSize = 1024;
    char buffer[bufferSize];

    if (pipe(pipefd) == -1) {
        std::cerr << "Failed to create pipe." << std::endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Failed to fork process." << std::endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]);  // Close the write end of the pipe

        int bytesRead = read(pipefd[0], buffer, bufferSize);
        std::cout << "Child process received: " << buffer << std::endl;

        close(pipefd[0]);  // Close the read end of the pipe
    } else {
        // Parent process
        close(pipefd[0]);  // Close the read end of the pipe

        std::string message = "Hello from the parent process!";
        write(pipefd[1], message.c_str(), message.length());

        close(pipefd[1]);  // Close the write end of the pipe
    }

    return 0;
}