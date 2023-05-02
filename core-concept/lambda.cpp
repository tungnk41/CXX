#include <iostream>
#include <string>
using namespace std;

void test(void (*pFunc)()){
    pFunc();
}

void testGreet(void (*pFunc)(string name)){
    pFunc("abc");
}
void testPlus(int (*pFunc)(int a, int b)){
    pFunc(1,2);
}


int main() {

    auto func = []() {
        cout << "lambda" <<endl;
    };
    auto greet = [](string name){
        cout << name <<endl;
    };
    auto plus = [](int a, int b) -> int {
        return a+b;
    };

    func();
    test(func);
    test( []() {cout << "lambda" <<endl;} );



    /***/

    int a = 5;
    int b = 10;

    //capture a,b by value
    auto _a = [a,b]() {
        cout << a << " " << b <<endl; 
    };
    //capture all local variable by value
    auto _b = [=]() {
        cout << a << " " << b <<endl; 
    };
    //default capture all local variable by value, but  capture b by reference
    auto _c = [=, &b]() {
        cout << a << " " << b <<endl; 
    };
    //default capture all local variable by reference
    auto _d = [&]() {
        cout << a << " " << b <<endl; 
    };
    //default capture all local variable by reference, but a by value
    auto _d = [&, a]() {
        cout << a << " " << b <<endl; 
    };
    _c();

    return 0;
}