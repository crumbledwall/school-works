#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
 
int count_blank(char string[]){
    int count = 0;
    for(int i = 0; i<strlen(string); i++){
        if(strncmp(&string[i]," ",1)==0){
            count++;
        }
    }
    return count;
}
int main(){
    char string[BUFSIZ] =  "";
    char save[BUFSIZ] = "";
    int sh = 0;
    while(1){
        printf("prompt>");
        scanf("%[^\n]%*c", string);
        if(strcmp(string, "exit")==0){
            exit(0);
        }
        sh = fork();
        if(sh==0){
            char *array[count_blank(string)+1];
            int i=0;
            array[i] = strtok(string," ");

            while(array[i]!=NULL)
            {
                array[++i] = strtok(NULL," ");
            }
            int status =  execvp(array[0],array);
            printf("Commod not found\n");
            exit(0);
        }
        if(sh!=0){
            wait(NULL);
        }
    }
    return 0;
}