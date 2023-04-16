#include <iostream>
#include <boost/math/special_functions/factorials.hpp>

int main()
{
    int num = 2;
    std::cout << "Factorial of " << num << " is " << boost::math::factorial<double>(num) << std::endl;
    system("pause");
    return 0;
}
