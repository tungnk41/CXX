#include <iostream>
#include <algorithm>

class A {
    private:
        int* i;
    public:
        A() {
            std::cout << "Default constructor" << std::endl;
        };
        A(int v) {
            std::cout << "Param constructor" << std::endl;
            i = new int;
            *i = v;
        };
        A(const A& a){ //copy constructor
            std::cout << "Copy constructor" << std::endl;
            i = new int;
            *i = *a.i;
        };
        A(A&& a){ //move constructor
         std::cout << "Move constructor" << std::endl;
           this->i = a.i;
           a.i = nullptr;
        };

        // copy assignment operator
        A& operator=(const A& other) {
            if (this != &other) {
                if(this->i == nullptr) {
                    this->i = new int;
                }
                this->i = other.i;
            }
            return *this;
        }

        // move assignment operator
        A& operator=(A&& other) {
           if (this != &other) {
                A(other);
            }
            return *this;
        }

        void print() {
            if(i != nullptr) {
                std::cout<<*i<<std::endl;
            }
        }
        virtual ~A() {
            delete i;
        };
};

int main()
{
    A a(2);
    A b(3);
    A c = std::move(b);
    a.print();
    b.print();
    c.print();

    return 0;
}