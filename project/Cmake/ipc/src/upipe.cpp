#include <upipe.h>

int UPipe::createPipe() {
	return pipe(fd);
};

bool UPipe::isParentProcess(pid_t pid) {
    return pid > 0;
}

void UPipe::uwrite(std::string msg) {
    cout << msg << endl;
    close(fd[READ_FD]);
	write(fd[WRITE_FD],msg.c_str(),msg.length());
};

std::string UPipe::uread() {
    close(fd[WRITE_FD]);
    std::string s;
    char c;
    while(read(fd[READ_FD],&c,1) > 0) {
        s.push_back(c);
    }
    return s;
};

void UPipe::test() {
    createPipe();
    pid_t pid = fork();
    if(isParentProcess(pid)) {
        cout << "Write" <<endl;
        uwrite("123");
    } else {
        cout << "Read" <<endl;
        cout << uread() << endl;;
    }
};