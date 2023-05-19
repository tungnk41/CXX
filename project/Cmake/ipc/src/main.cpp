#include <iostream>
#include <share_memory.hpp>

using std::cout;
using std::endl;

int main() {
 
  posix::ShareMemory ipc;
  ipc.run();

  return 0;
}