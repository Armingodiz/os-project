#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
    int ticks = get_ticks();
    printf(1, "ticks: %d\n", ticks);
    exit();
}