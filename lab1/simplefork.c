/**
 * This is a skeleton for the simplefork
 * assignment. The goal is just to get
 * familiar with fork()
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int arg, char *argv[]) {
  // remember, declarations first
  pid_t pid=0;

  // here you will add a nice fork and a switch
  // for example pid=fork();
  // and then test pid

  // this could go in the child part
  printf("Child spawned, pid=%d ppid=%d pgrp=%d\n",
         (int)getpid(),(int)getppid(),(int)getpgrp());
  sleep(2);

  // this could go in the parent part
  printf("Parent(%d) spawned child(%d)\n",
         (int)getpid(),(int)pid);
  sleep(2);
  //and do not forget the wait!

  return 0;
}
