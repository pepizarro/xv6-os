#include "kernel/types.h"

#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char message[] = "running multiproc...\n";
  write(1, message, sizeof(message));
  fprintf(2, "started parent process, pid: %d, priority: %d, boost: %d\n", getpid(), getpriority(), getboost());

  int procs = 5;

  for (int i = 0; i < procs; i++) {
    /*fprintf(2, "+ creating child process number: %d\n", i);*/
    int pid = fork();
    if (pid == 0) {
        while(1) {
            fprintf(2, "ejecutando proceso numero %d, pid: %d \n", i, getpid());
            sleep(10);
        }
    } else {
        /*fprintf(2, "parent process, pid: %d, priority: %d, boost: %d\n", getpid(), getpriority(), getboost());*/
        sleep(10);
    }
    /*fprintf(2, "parent process, pid: %d, priority: %d, boost: %d\n", getpid(), getpriority(), getboost());*/
  }
  
  exit(0);
}
