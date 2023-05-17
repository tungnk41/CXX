#ifndef _SHM_H_
#define _SHM_H_
    #include <iostream>
    #include <string>
    #include <cstring>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    using namespace std;

    class ShareMemory {
        private:
        key_t key;
        int shmid;
        public:
            ShareMemory() {
                key = ftok("shm",65); //65: project ID
            };
            ~ShareMemory() {
                 // destroy the shared memory
                shmctl(shmid,IPC_RMID,NULL);
            };
            void getShareMemSegment();
            char* attach();
            void detach(char* str);
            void write();
            void read();
            void run();

    };
#endif