#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

static sem_t send1_receive;
static sem_t receive_send1;
static sem_t send2_receive;
static sem_t receive_send2;
static sem_t send1_send2;

int msgid = 0;

typedef struct {
    long int    mtype; 
    char        mtext[BUFSIZ];
} msgstruct;

msgstruct msgbuf_write,msgbuf_read;

void *sender1(void *arg)
{
    printf("sender1 start sending\n");
    msgbuf_write.mtype = 1;
    char string[BUFSIZ] = "";
    while(strcmp(string, "exit\n")!=0){
        strcat(msgbuf_write.mtext, string);
        fgets(string, BUFSIZ, stdin);
    }
    strcat(msgbuf_write.mtext, "end1\n");
    msgsnd(msgid,(void *)&msgbuf_write,BUFSIZ,0);
    memset(msgbuf_write.mtext, 0, BUFSIZ);
    sem_post(&send1_receive);


    sem_wait(&receive_send1);
    
    msgrcv(msgid,(void *)&msgbuf_read, BUFSIZ,1,IPC_NOWAIT);
    printf("\nrecever replied:\n%s", msgbuf_read.mtext);
    memset(msgbuf_read.mtext, 0, BUFSIZ);

    sem_post(&send1_send2);
    return NULL;
}


void *sender2(void *arg)
{
    sem_wait(&send1_send2);
    printf("\n\nsender2 start sending\n");
    msgbuf_write.mtype = 1;
    char string[BUFSIZ] = "";
    while(strcmp(string, "exit\n")!=0){
        strcat(msgbuf_write.mtext, string);
        fgets(string, BUFSIZ, stdin);
    }
    strcat(msgbuf_write.mtext, "end2\n");
    msgsnd(msgid,(void *)&msgbuf_write,BUFSIZ,0);
    memset(msgbuf_write.mtext, 0, BUFSIZ);
    sem_post(&send2_receive);


    sem_wait(&receive_send2);
    
    msgrcv(msgid,(void *)&msgbuf_read, BUFSIZ,1,IPC_NOWAIT);
    printf("\nrecever replied:\n%s", msgbuf_read.mtext);
    memset(msgbuf_read.mtext, 0, BUFSIZ);

    return NULL;
}

void  *receiver(void *arg)
{

    sem_wait(&send1_receive);

    printf("\nrecever start receiving msg from sender1:\n");
    msgrcv(msgid,(void *)&msgbuf_read, BUFSIZ,1,IPC_NOWAIT);
    printf("%s", msgbuf_read.mtext);
    memset(msgbuf_read.mtext, 0, BUFSIZ);


    msgbuf_write.mtype = 1;
    strcpy(msgbuf_write.mtext, "over1");
    msgsnd(msgid,(void *)&msgbuf_write,BUFSIZ,0);
    memset(msgbuf_write.mtext, 0, BUFSIZ);
    sem_post(&receive_send1);

    sem_wait(&send2_receive);

    printf("\nrecever start receiving msg from sender2:\n");
    msgrcv(msgid,(void *)&msgbuf_read, BUFSIZ,1,IPC_NOWAIT);
    printf("%s", msgbuf_read.mtext);
    memset(msgbuf_read.mtext, 0, BUFSIZ);


    msgbuf_write.mtype = 1;
    strcpy(msgbuf_write.mtext, "over2");
    msgsnd(msgid,(void *)&msgbuf_write,BUFSIZ,0);
    memset(msgbuf_write.mtext, 0, BUFSIZ);
    sem_post(&receive_send2);

    return NULL;
}



int main()
{
    pthread_t thread_A;
    pthread_t thread_B;
    pthread_t thread_C;

    msgid=msgget(12333,IPC_CREAT|0644);

    sem_init(&send1_receive,0,0);
    sem_init(&send2_receive,0,0);
    sem_init(&receive_send1,0,0);
    sem_init(&receive_send2,0,0);
    sem_init(&send1_send2,0,0);


    pthread_create(&thread_A,NULL,sender1,NULL);
    pthread_create(&thread_B,NULL,receiver,NULL);
    pthread_create(&thread_C,NULL,sender2,NULL);

    pthread_join(thread_A,NULL);
    pthread_join(thread_B,NULL);
    pthread_join(thread_C,NULL);

    sem_destroy(&send1_receive);
    sem_destroy(&send2_receive);
    sem_destroy(&receive_send1);
    sem_destroy(&receive_send2);
    sem_destroy(&send1_send2);
    return 0;

}