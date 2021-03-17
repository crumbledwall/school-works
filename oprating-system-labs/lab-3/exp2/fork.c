#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t *sem_id1;
sem_t *sem_id2;
sem_t *sem_id3;
int pipefd[2];
char buf[BUFSIZ];

void parent(){
    sem_wait(sem_id3);
    printf("parent start to read:\n");
    if (read(pipefd[0], buf, BUFSIZ) < 0) {
        perror("write()");
        exit(1);
    }
    printf("%s\n", buf);
    sem_close(sem_id3);
}

void child1(){
    snprintf(buf, BUFSIZ, "Message from child1: My pid is: %d\n", getpid());
    if (write(pipefd[1], buf, strlen(buf)) < 0) {
        perror("write()");
        exit(1);
    }
    sem_post(sem_id1);
    printf("child1 finished writing\n");
}

void child2(){
    sem_wait(sem_id1);
    snprintf(buf, BUFSIZ, "Message from child2: My pid is: %d\n", getpid());
    if (write(pipefd[1], buf, strlen(buf)) < 0) {
        perror("write()");
        exit(1);
    }
    sem_close(sem_id1);
    sem_post(sem_id2);
    printf("child2 finished writing\n");
}

void child3(){
    sem_wait(sem_id2);
    snprintf(buf, BUFSIZ, "Message from child3: My pid is: %d", getpid());
    if (write(pipefd[1], buf, strlen(buf)) < 0) {
        perror("write()");
        exit(1);
    }
    sem_close(sem_id2);
    sem_post(sem_id3);
    printf("child3 finished writing\n");
}


int main()
{
    sem_id1 = sem_open("child1->child2", O_CREAT, 0600, 0);
    sem_id2 = sem_open("child2->child3", O_CREAT, 0600, 0);
    sem_id3 = sem_open("child3->parent", O_CREAT, 0600, 0);
    pid_t pid1, pid2, pid3;
    pipe(pipefd);
    pid1 = fork();
    if (pid1 != 0) {
        parent();
    } else {
        pid2 = fork();
        if (pid2 != 0) {
            child1();
        } else {
             pid3 = fork();
            if (pid3 != 0) {
                child2();
            } else {
                child3();
            }
        }
    }
    return 0;
}