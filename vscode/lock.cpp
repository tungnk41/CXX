#include <iostream>
#include <mutex>
#include <thread>

/*
mutex
recursive_mutex: use when mutex is called nested recursive
*/

/*
lock_guard : implements a strictly scope-based mutex ownership wrapper
unique_lock : implements movable mutex ownership wrapper
scoped_lock : c++17 : deadlock-avoiding RAII wrapper for multiple mutexes

std::lock_guard is cheaper than std::unique_lock
*/

/*
- Use a std::unique_lock instead of a std::lock_guard: A std::unique_lock allows more fine-grained control over the lock, 
including the ability to unlock and re-lock the same mutex multiple times. 
This can be useful in situations where a thread needs to temporarily release a lock to perform other tasks before re-acquiring it.

- Use a std::shared_mutex instead of a std::mutex: A std::shared_mutex allows multiple threads to read from a shared resource simultaneously, 
while ensuring that only one thread can write to the resource at a time. 
This can help to reduce contention for the lock and improve performance.
*/

std::recursive_mutex rmx;
std::mutex mx;

void recursive(int n) {
    std::unique_lock<std::recursive_mutex> lock(rmx);
    std::cout << "Acquired mutex, n = " << n << std::endl;
    if (n > 0) {
        recursive(n - 1);
    }
}
void lockGuard() {
    std::lock_guard<std::mutex> locker(mx); //Auto release when out scope
    std::cout << "access share resource"<< std::endl;
}
void uniqeLock() {
    std::unique_lock<std::mutex> locker(mx);
    std::cout << "access share resource"<< std::endl;
    locker.unlock();
}
/*
std::defer_lock is used to create the lock without immediately locking the mutex. This allows the mutexes to be locked in a specific order later using std::lock
std::lock_guard can also be used with std::adopt_lock to assume ownership of an already-locked mutex, but it does not support std::defer_lock

std::lock_gard : use with adopt_lock
std::uniqe_lock: use with defer_lock
*/
void optionPrameterLock() {
    std::unique_lock<std::mutex> locker(mx, std::defer_lock); //defer_lock doesn't lock immediately after created
    locker.lock();
    std::cout << "access share resource"<< std::endl;
    locker.unlock();

    std::mutex m1,m2;
    std::lock(m1,m2); //lock m1,m2...mn
    std::lock_guard<std::mutex> lock1(m1, std::adopt_lock); //adopt_lock: only take ownership of mutex for purpose to call unlock, do not lock at this moment, already locked with std::lock
    std::lock_guard<std::mutex> lock2(m2, std::adopt_lock);

}

std::mutex mtx1, mtx2;
void scopeLock() {
    std::scoped_lock<std::mutex, std::mutex> lock(mtx1, mtx2);
    std::cout << "Thread " << std::this_thread::get_id() << " acquired mutexes" << std::endl;
}
int main() {
    // uniqeLock();
    optionPrameterLock();
    return 0;
}