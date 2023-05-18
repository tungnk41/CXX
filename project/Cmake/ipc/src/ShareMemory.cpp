#include <share_memory.hpp>


void ShareMemory::getShareMemSegment(){
    //   cout << getpagesize() <<endl;
    // shmget takes multiple of pagesize
    shmid = shmget(key,SHM_SIZE,0666|IPC_CREAT);
};

char* ShareMemory::attach(){
    return (char*) shmat(shmid,(void*)0,0);
};

void ShareMemory::detach(char* str){
    shmdt(str);
};

void ShareMemory::write(){
    getShareMemSegment();
    std::string s = "abc";
    char* data = (char*) shmat(shmid,(void*)0,0);
    memset(data, 0, SHM_SIZE);
    std::strcpy(data, s.c_str());
    cout <<"write: " <<data<<endl;
};

void ShareMemory::read(){
    char* data = (char*) shmat(shmid,(void*)0,0);
    cout <<"Read Share mem: " << data <<endl;
};

void ShareMemory::run() {
    write();
    read();
}
