#ifndef _MAIN_H_
#define _MAIN_H_
#include "Calculator.h"
class Main {
    private:
        Calculator* calculator;
    public:
        Main();
        ~Main();
        int increase(int a);
};
#endif