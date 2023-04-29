#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
#define MAX 10000

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

int value = 0;

void increase(int &v)
{
    int t = MAX;
    while (t-- > 0)
    {
        v += 1;
    }
}

void decrease(int &v)
{
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
    std::thread t3([](int &v)
                   {
            int t = MAX;
            while(t-- > 0) {
                v += 150;
                std::this_thread::sleep_for(chrono::seconds(1));
            } },
                   std::ref(value));
    std::thread t4(A::run, object, value);

    t1.join();
    if (t1.joinable())
    {
        t1.join();
        // Neu thread join 2 lan se lam chuong trinh bi terminate
    }
    if(t2.joinable()) {
        t2.detach();
    }
    t3.join();
    t4.join();

    cout << value << endl;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    createThreadTest();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return 0;
}
