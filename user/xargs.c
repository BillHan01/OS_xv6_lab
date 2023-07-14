#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
  char buffer[512];
  char *args[MAXARG];
  int i;

  if (argc < 2) {
    fprintf(2, "usage: xargs command ...\n");
    exit(1);
  }

  // save the command in args
  for (i = 1; i < argc; i++) {
    args[i-1] = argv[i];
  }

  while (1) {
    int n = 0;

    // read a line from the standard input
    while (1) {
      if (read(0, &buffer[n], 1) != 1) {
        // EOF
        exit(0);
      }

      if (buffer[n] == '\n') {
        buffer[n] = 0;
        break;
      }

      n++;
    }

    args[argc-1] = buffer;
    args[argc] = 0;

    if (fork() == 0) {
      // in child process, exec the command
      exec(args[0], args);
      fprintf(2, "xargs: exec %s failed\n", args[0]);
      exit(1);
    }

    // in parent process, wait for child to finish
    wait(0);
  }
}
