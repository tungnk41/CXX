#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    std::string pipeName = "myfifo";
    int bufferSize = 1024;
    char buffer[bufferSize];

    // Create the named pipe
    mkfifo(pipeName.c_str(), 0666);

    // Open the named pipe for reading
    int fd = open(pipeName.c_str(), O_RDONLY);

    // Read from the named pipe
    int bytesRead = read(fd, buffer, bufferSize);
    std::cout << "Received: " << buffer << std::endl;

    // Close the named pipe
    close(fd);

    // Remove the named pipe file
    unlink(pipeName.c_str());

    return 0;
}

int main() {
    std::string pipeName = "myfifo";
    std::string message = "Hello from the writer process!";

    // Open the named pipe for writing
    int fd = open(pipeName.c_str(), O_WRONLY);

    // Write to the named pipe
    write(fd, message.c_str(), message.length());

    // Close the named pipe
    close(fd);

    return 0;
}