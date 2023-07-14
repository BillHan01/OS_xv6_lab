#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int isprime(int fd)
{
  int number, prime;
  if(read(fd, &prime, sizeof(int)) == 0) 
  {
    close(fd);
    exit(0);
  }
  printf("prime %d\n", prime);
  int new_pipe[2];
  pipe(new_pipe);
  if(fork() == 0) 
  {
    close(fd);
    close(new_pipe[1]);
    isprime(new_pipe[0]);
  } 
  else 
  {
    close(new_pipe[0]);
    while(read(fd, &number, sizeof(int)) != 0) 
    {
      if(number % prime != 0) {
        write(new_pipe[1], &number, sizeof(int));
      }
    }
    close(new_pipe[1]);
    wait(0);
    close(fd);
    exit(0);
  }
  return 0;
}

int main()
{
  int pipe_fd[2];
  pipe(pipe_fd);
  if(fork() == 0) 
  {
    close(pipe_fd[1]);
    isprime(pipe_fd[0]);
  } 
  else 
  {
    close(pipe_fd[0]);
    for(int i = 2; i <= 35; ++i) 
    {
      write(pipe_fd[1], &i, sizeof(int));
    }
    close(pipe_fd[1]);
    wait(0);
  }
  exit(0);
}
