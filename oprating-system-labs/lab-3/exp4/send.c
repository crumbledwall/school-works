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
    char string[BUFSIZ];
    sem_t *sem_1 = sem_open("receive", O_CREAT, 0600, 0);
    sem_t *sem_2 = sem_open("over1", O_CREAT, 0600, 0);

    if ((shmid = shmget(12333, BUFSIZ, 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
        shmid = shmget(12333, BUFSIZ, 0666);
    }
    p = (char *)shmat(shmid, NULL, 0);

    while(strcmp(string, "exit")!=0){
        scanf("%s", string);
        strcpy(p, string);
        sem_post(sem_1);
    }

    sem_wait(sem_2);
    sem_close(sem_2);

    printf(">%s", p);

    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL); 
    
    
    return 0;
}