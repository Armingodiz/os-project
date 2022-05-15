#include "types.h"
#include "stat.h"
#include "user.h"

#define PS 4090 // page size

int base = 0;
int limit = 6;

int thread_creator(void (*fn)(void *), void *args)
{
    void *f_ptr = malloc( 2 * PS);
    void *stack;

    if(f_ptr ==0){
        return -1;
    }

    int mod = (uint)f_ptr % PS;
    if(mod == 0){
        stack = f_ptr;
    }else{
        // aligning the stack to be ِdivisible by PS(4096 here)
        stack = f_ptr + (PS - mod);
    }

    int thread_id = thread_create((void *)stack);

    if(thread_id <0){
        printf(1,"failed to create_thread");
        return -1;
    }

    if(thread_id == 0){
        // execute the function in child thread
        (fn)(args);
        free(stack);
        exit();
    }

    return thread_id;

};

int incrementer(void* turn){
    base++;
    int id = thread_id();
    if(base == limit){
        printf(1, "[ID] %d ==> [Success]\n", id);
        sleep(100);
    }else{
        printf(1, "[ID] %d ==> [Failed]\n", id);
        sleep(100);
        id = thread_creator(incrementer, &turn);
        if(id < 0){
            printf(0, "error in creating thread");
            exit();
        }
        thread_join(id);
    }
}

// int stack[PS] __attribute__((aligned (PS)));
int stack[4096] __attribute__((aligned(4096)));
int x = 0;

int main(int argc, char *argv[])
{
    printf(1, "Base = %d, ", base);
    printf(1, "Limit= %d\n", limit);
    int turn = 1;
    int pid = thread_creator(incrementer, &turn);
    if(pid < 0){
        printf(0, "error in creating thread");
        exit();
    }
    int x = thread_join(pid);
    printf(1, "%d\n", x);
    exit();
}