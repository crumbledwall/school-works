#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/syscall.h>
#define __NR_MYTASKINFO 337

int main()
{
    char * name = (char*)malloc(1000);
    char * state = (char*)malloc(1000);
    int uid, euid;
    pid_t id;

	id = 10;
    syscall(__NR_MYTASKINFO, id, name, state, &uid, &euid);
    printf("%d %s %s %d %d\n", id, name, state, uid, euid);
    return 0;
}
