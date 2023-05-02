#include <iostream>


void print() {
    std::cout<< "print"<< std::endl;
}
void _print(int a) {
    std::cout<< "print "<< a << std::endl;
}

void funcAsParam(void (*_print)()) {
    _print();
}

void _funcAsParam(void (*_print)(int _t)) { //Func has param
    _print(1);
}

int main() {

    // void (*tPrint)() = print;
    // tPrint();

    // void (*tPrint)(int) = _print;
    // tPrint(1);

    _funcAsParam(_print);

    return 0;
}