#include <iostream>
#include <map>
#include <functional>
using std::make_pair;
using std::map;
using std::bind;
using namespace std::placeholders; 


void print(int a, int b){ std::cout << a << " " << b <<std::endl; };

int main(){
  map<const char, std::function<double(double, double)>> tab;
  tab.insert(make_pair('+', [](double a, double b){ return a + b; }));
  tab.insert(make_pair('-', [](double a, double b){ return a - b; }));
  tab.insert(make_pair('*', [](double a, double b){ return a * b; }));
  tab.insert(make_pair('/', [](double a, double b){ return a / b; }));

  std::cout << "3.5 + 4.5\t=  " << tab['+'](3.5, 4.5) << "\n";  //3.5 + 4.5	=  8
  std::cout << "3.5 - 4.5\t=  " << tab['-'](3.5, 4.5) << "\n";  //3.5 - 4.5	=  -1
  std::cout << "3.5 * 4.5\t=  " << tab['*'](3.5, 4.5) << "\n";  //3.5 * 4.5	=  15.75
  std::cout << "3.5 / 4.5\t=  " << tab['/'](3.5, 4.5) << "\n";  //3.5 / 4.5	=  0.777778



  auto func = bind(print,std::placeholders::_1,_2);
  func(1,3);
  
  return 0;
}