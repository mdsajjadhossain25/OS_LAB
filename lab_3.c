#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/prctl.h>

int main(int argc, char * argv[]){
    int n = atoi(argv[1]);
    pid_t pid[n];
    for(int i = 0; i < n; i++){
        pid[i] = fork();
        if(pid[i]==0){
            prctl(PR_SET_NAME, argv[i+2],NULL, NULL, NULL);
            sleep(10);
            printf("%s pid : %d\n", argv[i+2], getpid());
            exit(0);
        }
    }
    printf("parent pid = %d\n", getpid());
    for(int i=0; i<n; i++){
        wait(NULL);
    }
    return 0;
}