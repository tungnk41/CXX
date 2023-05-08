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
        template<class M>
        void setData(M data);
};

template<class T>
class Object<T>::A {

};

template<class T>
void print(T n) {
    std::cout << n; 
}

template<class T>
template<class M>
void Object<T>::setData(M data){};


#include <type_traits>
template <typename T>
T square(T x) {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");
    return x * x;
}

int main() {

    Object<std::string> o("1");
    o.print();

    print<int>(6);

    square<std::string>("a");
    
    return 0;
}