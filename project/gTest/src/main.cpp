#include "main.h"

Main::Main() {
    calculator = new Calculator();
}
Main::~Main() {
    delete calculator;
}
int Main::increase(int a) {
    int sum = 0;
    for (int i = 0; i<a; i++) {
        // 0, a => 0 + a = a
        // a, a => a + a = 2a
        // 2a, a => 2a + a = 3a
        sum = calculator->add(sum,a);
    }
    return sum;
}