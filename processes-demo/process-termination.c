#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  /* fork a child process */
  pid_t pid0;

  pid0 = fork();

  if (pid0 < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }

  else if (pid0 == 0) {
    /* child process */
    exit(2);
  }

  else {
    /* parent process */
    int status;
    wait(&status);
    printf("Child process 1 has completed it's execution with exit code %d\n",
           WEXITSTATUS(status));
  }

  return 0;
}
