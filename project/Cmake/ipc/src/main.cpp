#include <main.h>
#include <upipe.h>
#include <pipe.h>
#include <mq.h>
#include <shm.h>

int main() {
 
  ShareMemory shm;
  shm.test();
  return 0;
}