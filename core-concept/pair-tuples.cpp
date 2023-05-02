#include <iostream>
#include <utility>
#include <tuple>
using std::get;
using namespace std;

int main() {

  pair<int, int> pair1(1,1);
  pair<int, int> pair2 = make_pair(1,1);
  auto pair3 = make_pair("str", 3.14);

  tuple<int,int,int> tuple1(1, 3,4);
  tuple<int,int,int> tuple2 = make_tuple(1, 3,4);

  cout << pair1.first << ", " << pair1.second << "\n"; 
  cout << get<1>(tuple1) << ", " << get<2>(tuple1) << "\n";  //from 0->2

  


    return 0;
}