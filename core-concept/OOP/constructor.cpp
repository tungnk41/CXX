
#include <iostream>
using namespace std;

class A {
    private:
        int* i;
    public:
        A() =  default; // When create by A a, if this constructor does default => error occured, in this case, compiler will generate default value for member's class, *i = nullptr
        // A() =  delete; //Cannot create by A a, because this constructor already deleted
        explicit A(int v) {
            std::cout << "Param constructor" << std::endl;
            i = new int;
            *i = v;
        };
        explicit A(const A& a){ //copy constructor
            std::cout << "Copy constructor" << std::endl;
            i = new int;
            *i = *a.i;
        };
        explicit A(A&& a){ //move constructor
         std::cout << "Move constructor" << std::endl;
           this->i = a.i;
           a.i = nullptr;
        };

        // copy assignment operator
        A& operator=(const A& other) {
            if (this != &other) {
                // if(this->i == nullptr) {
                //     this->i = new int;
                // }
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
        void set(int n) {
            *i = n;
        }
        virtual ~A() {
            delete i;
        };
};


int main() {
    A a;

    // A a = b => copy constructor
    // a= b => run operator =
    return 0;
}