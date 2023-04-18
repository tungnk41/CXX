#include <iostream>
#include <algorithm>

class A {
    private:
        int* i;
        void swapDataWith(A a) {
            //    int* temp = i;
            //    i = a.i;
            //    a.i = temp;
            std::swap(i,a.i);
        }
    public:
        A() {
            std::cout << "A()" << std::endl;
        };
        A(int v) {
            std::cout << "A(int v)" << std::endl;
            i = new int;
            *i = v;
        };
        A(const A &a){ //copy constructor
            std::cout << "A(const A &a)" << std::endl;
            i = new int;
            *i = *a.i;
        };
        A(A &&a){ //move constructor
         std::cout << "A(A &&a)" << std::endl;
           swapDataWith(a);
        };

        // copy assignment operator
        A& operator=(const A &rhs) {
            if (&rhs != this) {
                A temp(rhs); // copy object data
                temp.swapDataWith(*this);
            }
            return *this;
        }

        // move assignment operator
        A& operator=(A &&rhs) {
            A temp(std::move(rhs)); // move object data
            temp.swapDataWith(*this);
            return *this;
        }

        void print() {
            std::cout<<*i<<std::endl;
        }
        virtual ~A() {
            delete i;
        };
};

int main()
{
    A a(1);
    A b(a);
    a.print();
    b.print();

    return 0;
}