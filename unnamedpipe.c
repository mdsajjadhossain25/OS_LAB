#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pipefd[2];
    char wrtmsg[] = "Hello from parent\n";
    char readmsge[100];
    int created = pipe(pipefd);

    pid_t pid = fork();
    if(pid == 0){
        close(pipefd[1]);
        read(pipefd[0], readmsge, sizeof(readmsge));
        printf("child received message: %s\n",readmsge);
        close(pipefd[0]);
        exit(0);
    }else{
        close(pipefd[0]);
        write(pipefd[1], wrtmsg, strlen(wrtmsg));
        close(pipefd[1]);
        wait(NULL);
    }

}