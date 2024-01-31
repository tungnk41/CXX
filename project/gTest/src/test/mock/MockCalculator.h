#include "../../Calculator.h"

class MockCalculator : public Calculator {
public:
    MOCK_METHOD(int, add, (int a, int b));
};

MockCalculator* mockCalculator;
int Calculator::add(int a, int b) {
    return mockCalculator->add(a,b);
}