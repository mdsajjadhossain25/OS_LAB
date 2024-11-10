#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// int main(){
//     pid_t p = fork();
//     if(p==0){
//         sleep(10);
//         printf("orphan child process running %d and my parent pid %d\n", getpid(), getppid());
//     }else{
//         printf("parent terminating\n");
//         exit(0);
//     }
// }

int main(){
    pid_t child = fork();
    if(child>0){
        sleep(10);
    }else if(child==0){
        printf("child pid = %d ", getpid());
        printf("Child terminating\n");
        exit(0);
    }
}