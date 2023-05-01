#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <thread>
#include <condition_variable>

std::mutex mx;
std::queue<int> queue;
std::condition_variable cond;
int data = 0;

void pub(int& data){

    while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> locker(mx);
        if (queue.empty()) {
            queue.push(data++);
            cond.notify_one();
        }
        locker.unlock();
    }
}

void sub() {
    while (1)
    {
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> locker(mx);
        cond.wait(locker, []() {return !queue.empty(); });

        int data = queue.front();
        queue.pop();
        std::cout << data << std::endl;

        locker.unlock();
    }
    
}
int main() {

    std::thread t1(pub, std::ref(data));
    std::thread t2(sub);

    t1.join();
    t2.join();
    return 0;
}