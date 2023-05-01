#include <iostream>
#include <atomic>

struct Data{
    Data(int i) {
        a = i;
    }
    int a;
};

void atomic_load() {
    std::atomic<int> counter(42);
    int value = counter.load();
    std::cout << "Counter value: " << value << std::endl;
}
void atomic_store() {
    std::atomic<int> counter(0);
    counter.store(42);
    std::cout << "Counter value: " << counter.load() << std::endl;
}
void atomic_exchange() {
    std::atomic<int> counter(42);
    int previousValue = counter.exchange(0);
    std::cout << "Previous counter value: " << previousValue << std::endl;
    std::cout << "Current counter value: " << counter.load() << std::endl;
}
void atomic_compare_swap() {
    std::atomic<int> counter(0);
    int expected = 0;
    int newValue = 1;
    while (!counter.compare_exchange_weak(expected, newValue)) {
        expected = 0;
        newValue = 1;
    }
    std::cout << "Counter value: " << counter.load() << std::endl;
}
void atomic_add() {
    std::atomic<int> counter(0);
    int increment = 1;
    int previousValue = counter.fetch_add(increment);
    std::cout << "Previous counter value: " << previousValue << std::endl;
    std::cout << "Current counter value: " << counter.load() << std::endl;
}

void atomic_struct() {
    std::atomic<Data> stData(1);
    Data expect = stData.load();
    Data newValue{5};

    //weak : compare successfully but swap can be failure => call again, co the bi fail nhieu lan, so lan attempt cos the cao, it ton chi phi
    //use :lightweight synchonize
    while (!stData.compare_exchange_weak(expect, newValue)) { 
        //return false if stData equal to expect value, 
        //return true if stData not equal to expect, and swap newValue to stData
        expect = stData.load();
    }

    //strong : giong nhu weak nhung can nhieu chi phi hon, khong bao h fail
    while (!stData.compare_exchange_strong(expect, newValue)) { 
        //return false if stData equal to expect value, 
        //return true if stData not equal to expect, and swap newValue to stData
        expect = stData.load();
    }
    std::cout << "Counter value: " << stData.load().a << std::endl;
    std::cout << "Counter value: " << stData.load().a << std::endl;

}

int main() {
    // atomic_load();
    // atomic_store();
    // atomic_compare_swap();
    // atomic_add();
    atomic_struct();
    return 0;
}