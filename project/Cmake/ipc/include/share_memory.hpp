#ifndef _SHM_HPP_
#define _SHM_HPP_
    #include <iostream>
    #include <string>
    #include <cstring>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <array>

    #include <stdlib.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/mman.h>
    #include <unistd.h>
    #include <mutex>
    using namespace std;

    #define SHM_SIZE 4096*1 //pagesize is 4096

    namespace sysv {
        class ShareMemory {
            private:
                key_t key;
                int shmid;
                int* segment;
                void attach();
                void detach();
            public:
                ShareMemory() {
                    key = ftok("shm",65); //65: project ID
                    shmid = shmget(key,SHM_SIZE,0666|IPC_CREAT);
                    attach();
                };
                ~ShareMemory() {
                    detach();
                    // destroy the shared memory
                    shmctl(shmid,IPC_RMID,NULL);
                };
                void write(int* data);
                void read();
                void run();
        };
    };

    namespace posix{
        class ShareMemory {
            private:
                /* shared memory file descriptor */
                int shm_fd;
                void* segment;
                void attach();
                void detach();
            public:
                ShareMemory() {
                    /* create the shared memory object */
                    shm_fd = shm_open("shm", O_CREAT | O_RDWR, 0666);
                    /* configure the size of the shared memory object */
                     ftruncate(shm_fd, SHM_SIZE);
                     attach();
                    std::cout << sizeof(segment)  <<std::endl;
                };
                ~ShareMemory() {
                    detach();
                    close(shm_fd);
                    shm_unlink("shm");
                };
                void write(int* data);
                void read();
                void run();
        };
    }

#endif