#include <iostream>
#include <array>
#include <vector>

using namespace std;

class A {
    private:
        int* i;
    public:
        A() {
            std::cout << "Default constructor" << std::endl;
        };
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
    array<array<int,3>,3> arr { {{1,2,3},{1,2,3},{1,2,3}} };
    vector<vector<int>> v2;
    vector<A> v;

    // v.emplace_back(2);
    // v.push_back(1);




    return 0;
}