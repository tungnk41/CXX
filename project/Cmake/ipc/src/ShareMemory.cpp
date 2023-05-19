#include <share_memory.hpp>

void sysv::ShareMemory::attach(){
    segment =  (int*) shmat(shmid,(void*)0,0);
};

void sysv::ShareMemory::detach(){
    shmdt(segment);
};

void sysv::ShareMemory::write(int* data){
    int* dest = (int*) shmat(shmid,(void*)0,0);
    memset(dest, 0, SHM_SIZE);
    memcpy(dest,data, sizeof(data));
    cout <<"write: " <<*data<<endl;
};

void sysv::ShareMemory::read(){
    int* data = (int*) shmat(shmid,(void*)0,0);

    cout <<"Read Share mem: " << *data <<endl;
};

void sysv::ShareMemory::run() {
    std::array<int,2> a{10,20};
    
    write(a.data());
    read();
}

//////////////////////////////////////////////////

void posix::ShareMemory::attach(){
    /* memory map the shared memory object */
    segment = (void*) mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
};

void posix::ShareMemory::detach(){
    munmap(segment,SHM_SIZE);
};

void posix::ShareMemory::write(int* data){
    memset(segment, 0, SHM_SIZE);
    memcpy(segment,data, sizeof(data));
    cout <<"write: " <<*data<<endl;
};

void posix::ShareMemory::read(){
    cout <<"Read Share mem: " << *(int*)segment << *(int*)(segment + sizeof(int))  <<endl;
};

void posix::ShareMemory::run() {
    std::array<int,2> a{10,20};
    
    write(a.data());
    read();
}
