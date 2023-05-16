#include <shm.h>


void ShareMemory::getShareMemSegment(){
    shmid = shmget(key,1024,0666|IPC_CREAT);
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
    char* data = (char*) shmat(shmid,(void*)0,0);;
    std::strcpy(data, s.c_str());
    cout <<"write: " <<data<<endl;
};

void ShareMemory::read(){
    char* data = (char*) shmat(shmid,(void*)0,0);;
    cout <<"Read Share mem: " << data <<endl;
};

void ShareMemory::test() {
    write();
    read();
}
