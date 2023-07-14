#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() 
{
    int p1[2], p2[2];
    char buf[10];
    pipe(p1);
    pipe(p2);

    if(fork() == 0)
    {
        // Child
        read(p1[0], buf, 1); // Read from parent
        printf("%d: received ping\n", getpid());
        write(p2[1], buf, 1); // Send to parent
        exit(0);
    } else 
    {
        // Parent
        write(p1[1], "p", 1); // Send to child
        wait(0);
        read(p2[0], buf, 1); // Read from child
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}