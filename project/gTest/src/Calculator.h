#ifndef _CAL_H_
#define _CAL_H_
class Calculator {
public:
    Calculator() = default;
    virtual ~Calculator() {}
    int add(int a, int b);
};
#endif