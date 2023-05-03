#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

//It works by allowing a limited number of processes or threads to access a shared resource at any given time.
class Semaphore {
private:
    int count;
    std::mutex mutex;
    std::condition_variable cv;
public:
    Semaphore(int count = 0) : count{count} {}

    void acquire() {
        std::unique_lock<std::mutex> lock{mutex};
        while (count == 0) {
            cv.wait(lock);
        }
        --count;
    }

    void release() {
        std::lock_guard<std::mutex> lock{mutex};
        ++count;
        cv.notify_one();
    }


};

Semaphore sem{1};
int shared_resource{0};

void worker() {
    sem.acquire();
    ++shared_resource;
    std::cout << "Worker: shared_resource=" << shared_resource << std::endl;
    sem.release();
}

int main() {
    std::thread t1{worker};
    std::thread t2{worker};

    t1.join();
    t2.join();

    return 0;
}