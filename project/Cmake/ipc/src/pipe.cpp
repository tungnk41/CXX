#include <pipe/pipe.hpp>

void Pipe::createFifo() {
    mkfifo(pipefifo.c_str(), 0666); //permission read & write
};

void Pipe::create(int type){
    if(type == 1) {
        runReceiver();
    }
    else {
        runSender();
    }
};

void Pipe::runReceiver(){
    std::string buff;
    int fd;
    char c;
     while(1) {
        fd = open(pipefifo.c_str(), O_RDONLY);
        while(read(fd,&c,1) > 0) {
            buff.push_back(c);
        }
        cout <<"Receive: " << buff <<endl;
        buff.clear();
        close(fd);
    }
};

void Pipe::runSender(){
    std::string buff;
    int fd;
    while(1) {
        std::cin >> buff;
        fd = open(pipefifo.c_str(),O_WRONLY);
        write(fd, buff.c_str(), buff.length());
        cout <<"Send: " <<buff<<endl;
        close(fd);
    }
};

void Pipe::run() {
    Pipe pipe;
    int type;

    cout << "1: Receiver "<<endl<<"2: Sender"<<endl;
    cin >> type;
    pipe.create(type);
}