#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
#define MAX 10000
std::mutex mx;
int value = 0;

class A
{
private:
    A();

public:
    A(int i){};
    void run(int v)
    {
        int t = MAX;
        while (t-- > 0)
        {
            v += 1;
        }
    }
};

void increase(int &v)
{
    std::unique_lock<mutex> locker(mx);
    int t = MAX;
    while (t-- > 0)
    {
        v += 1;
    }
    locker.unlock();
}

void decrease(int &v)
{
    std::lock_guard<mutex> locker(mx);
    int t = MAX;
    while (t-- > 0)
    {
        v += 1;
    }
}

void createThreadTest()
{
    A object{1};
    std::thread t1(increase, std::ref(value));
    std::thread t2(decrease, std::ref(value));
    std::thread t3([](int &v){
            int t = MAX;
            while(t-- > 0) {
                v += 150;
                std::this_thread::sleep_for(chrono::seconds(1));
            } },std::ref(value));
    std::thread t4(A::run, object, value);

    t1.join();
    if (t1.joinable())
    {
        t1.join();
        // Neu thread join 2 lan se lam chuong trinh bi terminate
    }
    if(t2.joinable()) {
        t2.join();
    }
    t3.join();
    t4.join();

    cout << value << endl;
}


std::exception_ptr gException = nullptr;
void handleThreadException() {
    try
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        throw std::runtime_error("Catch me in MAIN");
    }
    catch (...)
    {
        //Set the global exception pointer in case of an exception
        gException = std::current_exception();
    }

    /* in Main
        std::thread t1
        t1.join
        if(gException) {
            handle exception
        }
    */
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    // createThreadTest();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    int totalCurrencyThread = std::thread::hardware_concurrency();
    std::cout << totalCurrencyThread <<std::endl;

    return 0;
}
