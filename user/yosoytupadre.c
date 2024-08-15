
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  char message[] = "running yo soy tu padre...\n";
  write(1, message, sizeof(message));

  fprintf(2, "pid: %d\n", getpid());
  fprintf(2, "ppid: %d\n", getppid());
  fprintf(2, "ancestor(0): %d\n", getancestor(0));
  fprintf(2, "ancestor(1): %d\n", getancestor(1));
  fprintf(2, "ancestor(2): %d\n", getancestor(2));
  fprintf(2, "ancestor(3): %d\n", getancestor(3));
  
  exit(0);
}
