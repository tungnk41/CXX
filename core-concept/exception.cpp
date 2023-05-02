#include <iostream>
#include <exception>


void getExcep() {
    bool isParentException = false;

    if (isParentException)
    {
        throw std::exception();
    }
    else {
        throw std::bad_alloc();
    }
}
int main() {

    try
    {
        getExcep();
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "bad_alloc " << e.what() << '\n';
    }
     catch(const std::exception& e)
    {
        std::cerr << "exception " << e.what() << '\n';
    }
    
    return 0;
}