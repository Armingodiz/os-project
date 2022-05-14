#include "types.h"
#include "stat.h"
#include "user.h"

#define PS 4096

// int stack[PS] __attribute__((aligned (PS)));
int stack[4096] __attribute__((aligned(4096)));
int x = 0;

int func(int x){
    printf(1,"x isssss:%d\n",x);
}

int main(int argc, char *argv[])
{
    printf(1, "stackkk %d\n", stack);
    int tid = thread_creator(func,1);

    if (tid < 0)
    {
        printf(1, "can not create thread!\n");
    }
    exit();
}