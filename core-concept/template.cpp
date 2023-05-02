#include <iostream>
#include <string>

template<class T>
class Object {
    private:
        T obj;
        class A;
    public:
        Object(T obj) {
            this->obj = obj;
        }

        void print() {
            std::cout << obj;
        }
};

template<class T>
class Object<T>::A {

};

template<class T>
void print(T n) {
    std::cout << n; 
}

int main() {

    Object<std::string> o("1");
    o.print();

    print<int>(6);

    return 0;
}