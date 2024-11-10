#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(){
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);

    pid_t child = fork();
    if(child==0){
        sleep(1);
        char * shared_mem = (char*)shmat(shmid, NULL, 0);
        printf("Child Read: %s", shared_mem);
        shmdt(shared_mem);
        exit(0);

    }else{
        char *shared_mem = (char*)shmat(shmid, NULL, 0);
        char * msge = "Hello from the parent\n";
        strcpy(shared_mem, msge);
        printf("Parent wrote: %s", shared_mem);

        shmdt(shared_mem);
        wait(NULL);
        shmctl(shmid, IPC_RMID, NULL);
    }
}
