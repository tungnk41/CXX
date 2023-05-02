#include <iostream>
#include <typeinfo>


using namespace std;


int main() {
    string str;
    double d;

    if (typeid(double) == typeid(d))
    {
        cout << "compare typeId double" << endl;
    }

    if (typeid(str) != typeid(d))
    {
        cout << "compare typeId double with string" << endl;
    }
    
    cout << typeid(str).name() <<endl;    

    //decltype: lay ra kieu du lieu cua bien str
    decltype(str) name = "string";
    cout << typeid(str).name() <<endl;  

    return 0;
}