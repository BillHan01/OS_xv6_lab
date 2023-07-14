#include "kernel/types.h"
//#include "kernel/stat.h"
#include "user/user.h"


// user's sleep process
int main(int argc, char *argv[])
{
    // 2 arguments: program name and number of ticks
    if(argc != 2)
    {
        fprintf(2, "Correct Usage: sleep {ticks}\n");
        exit(1);
    }

    int ticks_num = atoi(argv[1]);
    if(ticks_num < 0)
    {
        fprintf(2, "Sleep ticks: invalid number '%s'\n", argv[1]);
        exit(1);
    }

    sleep(ticks_num);
    exit(0);
}