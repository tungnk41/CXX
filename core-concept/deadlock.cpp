#include <iostream>
#include <mutex>
#include <thread>

/*
 When a thread has more than one lock, there is a chance of deadlock
 Trong lap trinh, Deadlock thuong xay ra lien quan den thu tu lock cua cac mutex khong giong nhau

 Prevent deadlock:
- lock the two mutexes in the same order -> each thread acquires the necessary mutexes in a consistent order, which helps prevent deadlocks.
- use std::lock -> lock the same order, lock two or more mutexes at once without risk of deadlock
- moi share_resource can co 1 mutex rieng
*/

std::mutex m1, m2;
std::unique_lock<std::mutex> mutex1(m1, std::defer_lock);    
std::unique_lock<std::mutex> mutex2(m2, std::defer_lock); 

int shared_data1 = 0;
int shared_data2 = 0;

void thread_func1()
{
    // Acquire mutex1 before mutex2
    std::lock(mutex1, mutex2);
    std::cout << "Thread 1 locked mutex1 and mutex2." << std::endl;
    // Access shared_data1
    shared_data1 += 10;
    // Access shared_data2
    shared_data2 -= 5;
    // Unlock both mutexes in reverse order
    mutex2.unlock();
    mutex1.unlock();
}

void thread_func2()
{
    // Acquire mutex1 before mutex2
    std::lock(mutex1, mutex2);
    std::cout << "Thread 2 locked mutex1 and mutex2." << std::endl;
    // Access shared_data2
    shared_data2 += 8;
    // Access shared_data1
    shared_data1 -= 3;
    // Unlock both mutexes in reverse order
    mutex2.unlock();
    mutex1.unlock();
}

int main()
{
    // Create two threads that will both try to access shared_data1 and shared_data2
    std::thread t1(thread_func1);
    std::thread t2(thread_func2);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    std::cout << "Shared data1: " << shared_data1 << std::endl;
    std::cout << "Shared data2: " << shared_data2 << std::endl;

    return 0;
}