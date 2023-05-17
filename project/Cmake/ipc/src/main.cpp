#include <main.h>
#include <upipe.h>
#include <pipe.h>
#include <mq.h>
#include <shm.h>


int main() {
 
  MessageQueue ipc;
  ipc.run();

  return 0;
}