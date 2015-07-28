/**
 * server.c : this is the server part for the lab.
 * You should modify this program in 2 steps:
 * 1 - make it accept several connections at
 *     at the same time by using fork()
 * 2 - solve the zombie problem, which consumes
 *     resources and will make the program
 *     refuse connections after a while.
*/

#include "netstuff.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* change this to #define PART 2 if you want to try
the signal solution when solving part 2.
DO NOT FORGET TO REVERT TO #define PART 1 afterwards !
*/
#define PART 1


/* Signal Handler...
   don't care about this function in the first part...
   */
#if PART==2
void childHandler(int sig) {
  int status,pid;
  pid=wait(&status);
  fprintf(stdout,"Child server %d exited(%d)\n",pid,status);
}
#endif

/* main program */
int main(int argc,char** argv) {

#if PART==2
  struct sigaction my_sa, old_sa;
#endif
  int pid;
  int pid2; 

  initServer(argc,argv);
  printf("Server ready\n");

#if PART==2
    my_sa.sa_handler = childHandler;
    my_sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &my_sa, &old_sa); 
#endif  

  for(;;) {
    /* accept a connection */
    if(acceptConnection()!=0) {
      terminateServer();
    } else {

      /* you will need a fork here
         and use it as pid=fork();
         instead of the following which
         just fixes the pid variable */
        pid=fork();
        switch (pid) {
                case -1:
                        /* error: fork was unsuccessful */
                        printf("error: fork was unsuccessful");
                        exit(-1);
                case 0:
                        /* this is the child job */
                        pid2=fork();
                        if (pid2 == 0) {
                          pid2 = getpid();
                          connectionJob(pid2);
                          closeAccept(pid);
                        } 
                        exit(0);
                default:
                        wait(pid);
        }
    }
  }
}
