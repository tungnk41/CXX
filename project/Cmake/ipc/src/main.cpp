#include <main.hpp>
#include <upipe.hpp>
#include <pipe.hpp>
#include <mq.hpp>
#include <shm.hpp>


int main() {
 
  MessageQueue ipc;
  ipc.run();

  return 0;
}