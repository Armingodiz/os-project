#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
    int ticks = getTicks();
    printf(1, "ticks: %d", ticks);
    exit();
}
