
#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#define __NR_MYTASKMM 336

int main()
{
    unsigned long test[6] = {0};
    pid_t  id;
    id = getpid();
    syscall(__NR_MYTASKMM, id, test);
    for (int i = 0; i<6; i++){
        printf("%lx\n", test[i]);
    }
}