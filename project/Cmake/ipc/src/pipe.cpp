#include <pipe.h>

void Pipe::createFifo() {
    mkfifo(pipefifo.c_str(), 0666); //permission read & write
};

void Pipe::create(int type){
    if(type == 1) {
        createReader();
    }
    else {
        createSender();
    }
};

void Pipe::createReader(){
    cout << "Pipe::createReader" <<endl;
    std::string buff;
    int fd;
    char c;
     while(1) {
        fd = open(pipefifo.c_str(), O_RDONLY);
        while(read(fd,&c,1) > 0) {
            buff.push_back(c);
        }
        cout <<"Reader: " << buff <<endl;
        buff.clear();
        close(fd);
    }
};

void Pipe::createSender(){
    cout << "Pipe::createSender" <<endl;
    std::string buff;
    int fd;
    while(1) {
        std::cin >> buff;
        fd = open(pipefifo.c_str(),O_WRONLY);
        write(fd, buff.c_str(), buff.length());
        cout <<"Sender: " <<buff<<endl;
        close(fd);
    }
};

void Pipe::run() {
    Pipe pipe;
    int type;

    cout << "1: Reader "<<endl<<"2: Sender"<<endl;
    cin >> type;
    pipe.create(type);
}