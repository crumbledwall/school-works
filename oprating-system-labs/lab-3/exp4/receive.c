#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
    int shmid;
    char *p;
    sem_t *sem_1 = sem_open("receive", O_CREAT, 0600, 0);
    sem_t *sem_2 = sem_open("over1", O_CREAT, 0600, 0);


    if ((shmid = shmget(12333, BUFSIZ, 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
        shmid = shmget(12333, BUFSIZ, 0666);
    }
    p = (char *)shmat(shmid, NULL, 0);
    
    while(strcmp(p, "exit")!=0){
        sem_wait(sem_1);
        printf(">%s\n", p);
    }

    sem_close(sem_1);

    strcpy(p, "exit\n");

    sem_post(sem_2);

    return 0;
}