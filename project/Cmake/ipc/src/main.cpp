#include <iostream>
#include <string>
#include <upipe.hpp>
#include <pipe.hpp>
#include <mq.hpp>
#include <shm.hpp>
#include <signal.hpp>

using std::cout;
using std::endl;

int main() {
 
  Signal ipc;
  ipc.run();

  return 0;
}